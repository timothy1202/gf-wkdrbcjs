// SDL 
//
// written by changhoonpark@gmail.com

/*
#include "main.h"


SDL_Window*		g_pWindow = 0;
SDL_Renderer*	g_pRenderer = 0;

SDL_Texture*	g_pTexureImage;
SDL_Rect		g_RectImage;

SDL_Texture*	g_pTexureText;
SDL_Rect 		g_RectText;

TTF_Font*		g_pFont;
Mix_Chunk*		g_pChunk;

bool			g_bRunning = false;
bool			g_bLeftMousePressed = false;

bool init();
void handleInput();
void update();
void render();

int main(int argc, char* argv[])
{
	if (!init())
	{
		return 1; // something's wrong
	}

	g_bRunning = true;

	while (g_bRunning)
	{
		handleInput();
		update();
		render();
	}

	Mix_CloseAudio();
	Mix_Quit();
	TTF_CloseFont(g_pFont);
	TTF_Quit();
	SDL_Quit();

	return 0;
}

bool init()
{
	SDL_Surface* pTempSurface;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
		return false;
	}

	g_pWindow = SDL_CreateWindow("HoseoSDL.2022",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_SHOWN);
	if (g_pWindow == NULL)
	{
		SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
		return false;
	}

	g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
	if (g_pRenderer == NULL)
	{
		SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		// SDL Image
		pTempSurface = IMG_Load("./assets/animate-alpha.png");
		if (pTempSurface == NULL)
		{
			SDL_Log("IMG_Load Error: %s\n", IMG_GetError());
			return false;
		}
		else
		{
			g_pTexureImage = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
			g_RectImage = { 0, 0, 128, 82 };
			SDL_FreeSurface(pTempSurface);
		}
	}

	// SDL TTF 
	if (TTF_Init() < 0)
	{
		SDL_Log("TTF_Init Error: %s\n", TTF_GetError());
		return false;
	}
	else
	{
		g_pFont = TTF_OpenFont("./assets/NanumGothic.ttf", 20);
		if (g_pFont == NULL)
		{
			SDL_Log("TTF_OpenFont Error: %s\n", TTF_GetError());
			return false;
		}
		else
		{
			// SDL TTF
#ifdef UNICODE
			pTempSurface = TTF_RenderUNICODE_Shaded(g_pFont, (Uint16*)L"한글 텍스쳐",
				SDL_Color{ 0, 0, 255 }, SDL_Color{ 255, 255, 255 });
#else
			pTempSurface = TTF_RenderUTF8_Shaded(g_pFont, "한글 텍스쳐",
				SDL_Color{ 0, 0, 255 }, SDL_Color{ 255, 255, 255 });
#endif
			if (pTempSurface == NULL)
			{
				SDL_Log("TTF_Render Error: %s\n", TTF_GetError());
				return false;
			}
			else
			{
				g_pTexureText = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
				g_RectText = { 0, 0, pTempSurface->w, pTempSurface->h };
				SDL_FreeSurface(pTempSurface);
			}
		}

	}

	// SDL Mixer 
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("Mix_OpenAudio Error: %s\n", Mix_GetError());
		return false;
	}
	else
	{
		g_pChunk = Mix_LoadWAV("./assets/jump.wav");
		if (g_pChunk == NULL)
		{
			SDL_Log("Mix_LoadWAV Error : %s\n", Mix_GetError());
			return false;
		}
		else
		{
			Mix_Volume(-1, 128);
		}
	}

	return true;
}

void handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_bRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_bLeftMousePressed = true;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_bLeftMousePressed = false;
			}
			break;

		}
	}
}

void update()
{
	if (g_bLeftMousePressed)
	{
		// chunk에 담긴 사운드 재생, -1은 가장 가까운 채널, 0은 반복 횟수
		Mix_PlayChannel(-1, g_pChunk, 0);
		printf("왼쪽클릭 눌림 - 사운드 재생\n");
	}
}

void render()
{
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer);

	SDL_RenderCopy(g_pRenderer, g_pTexureImage, &g_RectImage, &g_RectImage);
	SDL_RenderCopy(g_pRenderer, g_pTexureText, &g_RectText, &g_RectText);
	filledCircleColor(g_pRenderer, 300, 300, 50, 0xFFFF0000);

	SDL_RenderPresent(g_pRenderer);
}*/

//#include <SDL.h>
#include "main.h"
#include <conio.h>

//	SDL 함수?
SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

//	g_bRunning의 역할?
bool g_bRunning = false;


// main에서 Init을 함수로 빼냄
bool init(const char* title, int xpos, int ypos,
	int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		g_pWindow = SDL_CreateWindow(title,
			xpos, ypos,
			height, width, 
			flags);

		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
	}
	else
	{
		return false;
	}

	// 화면 그려줄 값 g_pRenderer을 초기화
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

	return true;
}

// Init에서 설정된g_pRenderer 값으로 화면을 그려줄 것임.
void render()
{
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);
}

// 키입력
void getCommand()
{
	if (_kbhit())
	{
		if (_getch() == 27)
		{
			g_bRunning = false;
		}
	}
}

void update()
{
	SDL_SetRenderDrawColor(g_pRenderer, rand() % 256, rand() % 256, rand() % 256, 255);
	SDL_Delay(1000);
}

int main(int argc, char* args[])
{
#pragma region MainInInit
	/*if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{

		g_pWindow = SDL_CreateWindow("Setting up SDL",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640, 480, //화면 크기 비율?
			SDL_WINDOW_SHOWN);

		if (g_pWindow != 0)
		{
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}
	}
	else
	{
		return 1;
	}

	//	화면 지우기
	//	r,g,b,a a는 투명도(0(투명)~255(불투명))
	//  r,g,b,a 값을 g_pRenderer에 설정
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255); //검은색 배경
	//SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 255); //파란 배경
	//SDL_SetRenderDrawColor(g_pRenderer, 255, 0, 255, 255); //보라색 배경
	//SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255); //하얀색 배경

	// g_pRenderer값으로 화면을 그려줌
	SDL_RenderClear(g_pRenderer);
	SDL_RenderPresent(g_pRenderer);

	//5초 대기후 종료
	SDL_Delay(5000);
	SDL_Quit();
	return 0;*/

#pragma endregion

#pragma region MainOutInit

	if (init("Breaking Up HelloSDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480,
		SDL_WINDOW_SHOWN))
	{
		g_bRunning = true;
	}
	else
	{
		return 1; // something's wrong
	}

	while (g_bRunning)
	{
		getCommand();
		render();
		update();
	}
	// g_bRunning의 역할 - while 문의 조건
	// render함수를 동작하기 위해 통제하기 위해서 사용
	// g_bRunning는 메인 밖으로 빼낸 Init(true or false를 반환)의 반환값에 의해 true로 변경되고 while문의 조건을 만족하여 화면을 그려주는 render함수가 동작하게 됨.

	SDL_Quit();
	return 0;

#pragma endregion
}
