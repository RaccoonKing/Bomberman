#include "stdafx.h"
#include "InputManager.h"
#include "Player.h"




InputManager::InputManager()
{
	m_iXS = 0;
	m_iYS = 0;
}

InputManager::~InputManager()
{
}

int InputManager::GetSpeedX()
{
	return m_iXS;
}

int InputManager::GetSpeedY()
{
	return m_iYS;
}

void InputManager::HandleKeyEvents()
{
	SDL_Event xEvent;
	while (SDL_PollEvent(&xEvent))
	{
		switch (xEvent.type)
		{
		case SDL_KEYDOWN:
			switch (xEvent.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_iXS = -3;
				break;
			case SDLK_RIGHT:
				m_iXS = 3;
				break;
			case SDLK_UP:
				m_iYS = -3;
				break;
			case SDLK_DOWN:
				m_iYS = 3;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (xEvent.key.keysym.sym)
			{
			case SDLK_LEFT:
				m_iXS = 0;
				break;
			case SDLK_RIGHT:
				m_iXS = 0;
				break;
			case SDLK_UP:
				m_iYS = 0;
				break;
			case SDLK_DOWN:
				m_iYS = 0;
				break;
			default:
				break;
			}
			
		}
	}
}



