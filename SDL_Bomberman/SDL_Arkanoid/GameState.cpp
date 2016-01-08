#include "stdafx.h"
#include "GameState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "Brick.h"
#include "Floor.h"
#include "InputManager.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <iostream>

GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayer = nullptr;



	

	/*
	// My temporary music loading, removed this because it was
	m_xMusic = Mix_LoadMUS("..path to music file");
	if (m_xMusic == nullptr)
	{
		const char* error = Mix_GetError();
		SDL_Log(error);
	}
	*/
}

GameState::~GameState()
{


	// My temporary music resource freeing
	/*Mix_FreeMusic(m_xMusic);
	m_xMusic = nullptr;*/
}

void GameState::Enter()
{
	//Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 0, 40, 40);
	//SDL_Rect* xRect = xSprite->GetRegion();
	//int iHeight = xRect->h;

	EnterWalls();
	EnterFloor();

	m_pxPlayer = new Player(m_xSystem.m_pxInputManager, m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Player.bmp", 0, 0, 40, 40), 60, 40);
	
}

void GameState::Exit()
{
	auto it = m_apxBricks.begin();
	while (it != m_apxBricks.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it)->GetSprite());
		delete (*it);
		it++;
	}
	m_apxBricks.clear();

	auto it2 = m_apxFloor.begin();
	while (it2 != m_apxFloor.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it2)->GetSprite());
		delete (*it2);
		it2++;
	}
	m_apxFloor.clear();

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxPlayer->GetSprite());
	delete m_pxPlayer;
	m_pxPlayer = nullptr;
}

bool GameState::Update(float p_fDeltaTime)
{
	m_pxPlayer->Update(p_fDeltaTime);

	// Moved the collision code to separate it from our Update code.
	//CheckCollision();
	return true;
	
}

void GameState::Draw()
{
	auto it = m_apxBricks.begin();
	while (it != m_apxBricks.end())
	{
		m_xSystem.m_pxDrawManager->Draw(
			(*it)->GetSprite(),
			(*it)->GetX(),
			(*it)->GetY());
		it++;
	}
	auto it2 = m_apxFloor.begin();
	while (it2 != m_apxFloor.end())
	{
		m_xSystem.m_pxDrawManager->Draw(
			(*it2)->GetSprite(),
			(*it2)->GetX(),
			(*it2)->GetY());
		it2++;
	}
	
	m_xSystem.m_pxDrawManager->Draw(m_pxPlayer->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
}

IState* GameState::NextState()
{
	return nullptr;
}

void GameState::CheckCollision()
{
	// The overlap variables will be passed as reference in the CollisionManagers Check collision function and in
	// the check function collision and potential overlap will be calculated.
	int iOverlapX = 0;
	int iOverlapY = 0;
	
}

void GameState::EnterWalls()
{
	for (int i = 0; i < 15; i++)
	{
		if (i == 0 || i == 14)
		{
			for (int j = 0; j < 19; j++)
			{

				Brick* pxBrick = new Brick(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 0, 40, 40), 20 + 40 * j, i * 40);
				m_apxBricks.push_back(pxBrick);
			}
		}
		else if (i % 2 == 1)
		{
			Brick* pxBrick = new Brick(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 0, 40, 40), 20, i * 40);
			m_apxBricks.push_back(pxBrick);
			pxBrick = new Brick(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 0, 40, 40), 740, i * 40);
			m_apxBricks.push_back(pxBrick);

		}
		else
		{
			for (int j = 0; j < 10; j++)
			{
				Brick* pxBrick = new Brick(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 0, 40, 40), 20 + 80 * j, i * 40);
				m_apxBricks.push_back(pxBrick);
			}
		}
	}
}

void GameState::EnterFloor()
{
	for (int i = 0; i < 16; i++)
	{
		Floor* pxFloor = new Floor(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 40, 40, 40, 40), 100 + i * 40, 40);
		m_apxFloor.push_back(pxFloor);
	}

	for (int i = 0; i < 12; i++)
	{
		Floor* pxFloor = new Floor(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 200, 0, 40, 40), 60, 40 * i + 80);
		m_apxFloor.push_back(pxFloor);
	}
	for (int j = 0; j < 6; j++)
		for (int i = 0; i < 16; i++)
		{
			Floor* pxFloor = new Floor(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 80, 0, 40, 40), 40 * i + 100, 120 + j * 80);
			m_apxFloor.push_back(pxFloor);
			i++;
			pxFloor = new Floor(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 160, 0, 40, 40), 100 + 40 * i,  120 + j * 80);
			m_apxFloor.push_back(pxFloor);
		}
	for (int j = 0; j < 6; j++)
		for (int i = 0; i < 8; i++)
		{
			Floor* pxFloor = new Floor(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 120, 0, 40, 40), 80 * i + 140, 80 + j * 80);
			m_apxFloor.push_back(pxFloor);
		}
	Floor* pxFloor = new Floor(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 40, 40, 40), 60, 40);
	m_apxFloor.push_back(pxFloor);
}
