
#include "Game.h"

// main에서 Init을 함수로 빼냄
bool Game::init(const char* title, int xpos, int ypos,
	int height, int width, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0)
			{
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else
			{
				return false; // 랜더러 생성 실패
			}
		}
		else 
		{
			return false; // 윈도우 생설 실패 l
		}
	}
	else 
	{
		return false; // SDL 초기화 실패
	}
#pragma region a
#pragma endregion


#pragma region Texture 생성
	SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");
	
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);
#pragma endregion
	
#pragma region 원본상자 크기 초기화
	SDL_QueryTexture(m_pTexture, NULL, NULL,
		&m_sourceRectangle.w, &m_sourceRectangle.h);
#pragma endregion
	
#pragma region 대상상자 크기 초기화
	// 원본 상자의 크기를 대상 상자와 같은 크기가 되도록 설정
	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;
#pragma endregion


#pragma region 원본/대상 상자의 위치 설정
	// 원본과 대상의 위치 또한 같도록
	m_destinationRectangle.x = m_sourceRectangle.x = 0;
	m_destinationRectangle.y = m_sourceRectangle.y = 0;
#pragma endregion


	m_bRunning = true;
	return true;
}
// 키입력
void Game::getCommand()
{
	if (_kbhit())
	{
		if (_getch() == 27)
		{
			m_bRunning = false;
		}
	}
}

void Game::update()
{
}

// Init에서 설정된g_pRenderer 값으로 화면을 그려줄 것임.
void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);

	SDL_RenderPresent(m_pRenderer);

	
}

bool Game::running()
{
	return m_bRunning;
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				m_bRunning = false;
				break;
			default:
				break;
		}
	}
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}