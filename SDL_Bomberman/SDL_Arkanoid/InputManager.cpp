#include "stdafx.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "Player.h"




InputManager::InputManager()
{
	m_iXS = 0;
	m_iYS = 0;
	m_bQuit = false;
	m_iActiveBombAmount = 0;
	m_iAllowedBombAmount = 1;
	m_bLayBomb = 0;

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

bool InputManager::CheckQuit()
{
	return m_bQuit;
}

bool InputManager::CheckBomb()
{
	if (m_iAllowedBombAmount >= m_iActiveBombAmount)
	{
		m_bLayBomb = 0;
		m_iActiveBombAmount + 1;
		PlaceBomb = true;
		return PlaceBomb;

	}
	else
	{
		PlaceBomb = false;
		return PlaceBomb;
	}
}

int InputManager::CheckLayBomb()
{
	return m_bLayBomb;
}

void InputManager::AddBombAmount()
{
	m_iAllowedBombAmount + 1;
}


void InputManager::SetActiveBombAmount()
{
	if(m_iActiveBombAmount > 0)
		m_iActiveBombAmount - 1;
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
				m_iXS = -2;
				break;
			case SDLK_RIGHT:
				m_iXS = 2;
				break;
			case SDLK_UP:
				m_iYS = -2;
				break;
			case SDLK_DOWN:
				m_iYS = 2;
				break;
			case SDLK_ESCAPE:
				m_bQuit = true;
				break;
			case SDLK_LSHIFT:
				m_bLayBomb = 1;
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
		break;
	}
	
	
}



