#include "stdafx.h"
#include "GameState.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "Brick.h"
#include "Floor.h"
#include "Bomb.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <iostream>
#include "AnimatedSprite.h"

GameState::GameState(System& p_xSystem)
{
	m_xSystem = p_xSystem;
	m_pxPlayer = nullptr;
	m_pxInputmanager = nullptr;
	StillSprite = 0;
	DumpPosition = 900;
	for (int i = 0; i < 10; i++)
	{
		m_iSetBombPositionX[i] = DumpPosition;
		m_iSetBombPositionY[i] = DumpPosition;
		m_iBombTimer[i] = 0;
	}
	m_iBombDeployment = 0;
	m_iBT = 0;

	

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
	Sprite* xSprite = m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 0, 40, 40);
	SDL_Rect* xRect = xSprite->GetRegion();
	int iHeight = xRect->h;

	EnterWalls();
	EnterFloor();

	m_pxPlayer = new Player(m_xSystem.m_pxInputManager, m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Player.bmp", 0, 200, 40, 40), 60, 40);

	m_pxStillPlayerRight = new Player(m_xSystem.m_pxInputManager, m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Player.bmp", 0, 0, 40, 40), DumpPosition, DumpPosition);
	m_pxStillPlayerLeft = new Player(m_xSystem.m_pxInputManager, m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Player.bmp", 0, 80, 40, 40), DumpPosition, DumpPosition);
	m_pxStillPlayerUp = new Player(m_xSystem.m_pxInputManager, m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Player.bmp", 0, 40, 40, 40), DumpPosition, DumpPosition);
	m_pxStillPlayerDown = new Player(m_xSystem.m_pxInputManager, m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Player.bmp", 0, 120, 40, 40), DumpPosition, DumpPosition);

	m_pxInputmanager = new InputManager();
	
	EnterAnimatedSprites();
	
	
	EnterBombs();
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

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxStillPlayerRight->GetSprite());
	delete m_pxStillPlayerRight;
	m_pxStillPlayerRight = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxStillPlayerLeft->GetSprite());
	delete m_pxStillPlayerLeft;
	m_pxStillPlayerLeft = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxStillPlayerUp->GetSprite());
	delete m_pxStillPlayerUp;
	m_pxStillPlayerUp = nullptr;

	m_xSystem.m_pxSpriteManager->DestroySprite(m_pxStillPlayerDown->GetSprite());
	delete m_pxStillPlayerDown;
	m_pxStillPlayerDown = nullptr;

	delete m_pxInputmanager;
	m_pxInputmanager = nullptr;

	auto it3 = m_apxBomb.begin();
	while (it3 != m_apxBomb.end())
	{
		m_xSystem.m_pxSpriteManager->DestroySprite((*it3)->GetSprite());
		delete (*it3);
		it3++;
	}


	
}

bool GameState::Update(float p_fDeltaTime)
{
	m_pxAnimatedSpriteRight->Update(p_fDeltaTime);
	m_pxAnimatedSpriteLeft->Update(p_fDeltaTime);
	m_pxAnimatedSpriteUp->Update(p_fDeltaTime);
	m_pxAnimatedSpriteDown->Update(p_fDeltaTime);
	m_pxPlayer->Update(p_fDeltaTime);

	//Bombs update
	{
		m_pxAnimatedBomb0->Update(p_fDeltaTime);
		m_pxAnimatedBomb1->Update(p_fDeltaTime);
		m_pxAnimatedBomb2->Update(p_fDeltaTime);
		m_pxAnimatedBomb3->Update(p_fDeltaTime);
		m_pxAnimatedBomb4->Update(p_fDeltaTime);
		m_pxAnimatedBomb5->Update(p_fDeltaTime);
		m_pxAnimatedBomb6->Update(p_fDeltaTime);
		m_pxAnimatedBomb7->Update(p_fDeltaTime);
		m_pxAnimatedBomb8->Update(p_fDeltaTime);
		m_pxAnimatedBomb9->Update(p_fDeltaTime);
	}
	

	// Moved the collision code to separate it from our Update code.
	CheckCollision();
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

		m_xSystem.m_pxDrawManager->Draw(
			m_pxPlayer->GetSprite(), 
			m_pxPlayer->GetX(), 
			m_pxPlayer->GetY());	


		DrawPlayer();
		CheckBombs();
		DrawBombs();
		
		
		
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
	bool Pushed = false;
	auto it = m_apxBricks.begin();
	while (it != m_apxBricks.end())
	{
		if (CollisionManager::Check((*it)->GetCollider(), m_pxPlayer->GetCollider(), iOverlapX, iOverlapY))
		{
			
			if (Pushed == false)
			{

				m_pxPlayer->SetPosition(m_pxPlayer->GetX() - iOverlapX, m_pxPlayer->GetY() - iOverlapY);
				Pushed = true;
			}
			else
				Pushed = false;
		}
		it++;
	}
	
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

void GameState::EnterAnimatedSprites()
{
	m_pxAnimatedSpriteRight =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Player.bmp");

	m_pxAnimatedSpriteRight->AddFrame(40, 0, 40, 40, 0.1f);
	m_pxAnimatedSpriteRight->AddFrame(80, 0, 40, 40, 0.1f);
	m_pxAnimatedSpriteRight->AddFrame(120, 0, 40, 40, 0.1f);
	m_pxAnimatedSpriteRight->AddFrame(160, 0, 40, 40, 0.1f);

	m_pxAnimatedSpriteLeft =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Player.bmp");

	m_pxAnimatedSpriteLeft->AddFrame(40, 80, 40, 40, 0.1f);
	m_pxAnimatedSpriteLeft->AddFrame(80, 80, 40, 40, 0.1f);
	m_pxAnimatedSpriteLeft->AddFrame(120, 80, 40, 40, 0.1f);
	m_pxAnimatedSpriteLeft->AddFrame(160, 80, 40, 40, 0.1f);

	m_pxAnimatedSpriteUp =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Player.bmp");

	m_pxAnimatedSpriteUp->AddFrame(40, 40, 40, 40, 0.1f);
	m_pxAnimatedSpriteUp->AddFrame(80, 40, 40, 40, 0.1f);
	m_pxAnimatedSpriteUp->AddFrame(120, 40, 40, 40, 0.1f);
	m_pxAnimatedSpriteUp->AddFrame(160, 40, 40, 40, 0.1f);

	m_pxAnimatedSpriteDown =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Player.bmp");

	m_pxAnimatedSpriteDown->AddFrame(40, 120, 40, 40, 0.1f);
	m_pxAnimatedSpriteDown->AddFrame(80, 120, 40, 40, 0.1f);
	m_pxAnimatedSpriteDown->AddFrame(120, 120, 40, 40, 0.1f);
	m_pxAnimatedSpriteDown->AddFrame(160, 120, 40, 40, 0.1f);

	
}

void GameState::DrawPlayer()
{
	
	
	
	
	if (m_pxPlayer->GetSpeedX() == 2)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedSpriteRight,
			m_pxPlayer->GetX(),
			m_pxPlayer->GetY());
		StillSprite = 3;
	}
	else if (m_pxPlayer->GetSpeedX() == -2)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedSpriteLeft,
			m_pxPlayer->GetX(),
			m_pxPlayer->GetY());
		StillSprite = 2;
	}
	else if (m_pxPlayer->GetSpeedY() == -2)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedSpriteUp,
			m_pxPlayer->GetX(),
			m_pxPlayer->GetY());
		StillSprite = 1;
	}
	else if (m_pxPlayer->GetSpeedY() == 2)
	{
		m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedSpriteDown,
			m_pxPlayer->GetX(),
			m_pxPlayer->GetY());
		StillSprite = 0;
		
	}
	else
	{
		

		if (StillSprite == 0)
			m_xSystem.m_pxDrawManager->Draw(m_pxStillPlayerDown->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
		else if (StillSprite == 1)
			m_xSystem.m_pxDrawManager->Draw(m_pxStillPlayerUp->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
		else if (StillSprite == 2)
			m_xSystem.m_pxDrawManager->Draw(m_pxStillPlayerLeft->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
		else if (StillSprite == 3)
			m_xSystem.m_pxDrawManager->Draw(m_pxStillPlayerRight->GetSprite(), m_pxPlayer->GetX(), m_pxPlayer->GetY());
		

	}
}

void GameState::EnterBombs()
{
	for (int i = 0; i < 10; i++)
	{
		Bomb* pxBomb = new Bomb(m_xSystem.m_pxSpriteManager->CreateSprite("../assets/Template.bmp", 0, 240, 40, 40), DumpPosition, DumpPosition, SDL_GetTicks());
		m_apxBomb.push_back(pxBomb);
	}

	m_pxAnimatedBomb0 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb0->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb0->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb0->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb0->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb0->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb0->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb1 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb1->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb1->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb1->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb1->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb1->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb1->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb2 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb2->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb2->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb2->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb2->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb2->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb2->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb3 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb3->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb3->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb3->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb3->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb3->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb3->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb4 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb4->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb4->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb4->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb4->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb4->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb4->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb5 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb5->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb5->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb5->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb5->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb5->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb5->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb6 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb6->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb6->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb6->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb6->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb6->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb6->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb7 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb7->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb7->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb7->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb7->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb7->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb7->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb8 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb8->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb8->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb8->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb8->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb8->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb8->AddFrame(200, 200, 40, 40, 0.45f);

	m_pxAnimatedBomb9 =
		m_xSystem.m_pxSpriteManager->
		CreateAnimatedSprite("../assets/Template.bmp");

	m_pxAnimatedBomb9->AddFrame(0, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb9->AddFrame(40, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb9->AddFrame(80, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb9->AddFrame(120, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb9->AddFrame(160, 200, 40, 40, 0.45f);
	m_pxAnimatedBomb9->AddFrame(200, 200, 40, 40, 0.45f);
}

void GameState::CheckBombs()
{
	if (m_pxInputmanager->CheckLayBomb() == 1)
	{
		if (m_pxInputmanager->CheckBomb())
		{

			m_iSetBombPositionX[m_iBombDeployment] = m_pxPlayer->GetX();
			m_iSetBombPositionY[m_iBombDeployment] = m_pxPlayer->GetY();
			m_iBombTimer[m_iBT] = SDL_GetTicks();
			m_iBT++;
			m_iBombDeployment++;
			if (m_iBT == 10)
				m_iBT = 0;
			if (m_iBombDeployment == 10)
				m_iBombDeployment = 0;
		}
	}

	if (m_iBombTimer[0] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[0] = DumpPosition;
		m_iSetBombPositionY[0] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[1] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[1] = DumpPosition;
		m_iSetBombPositionY[1] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[2] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[2] = DumpPosition;
		m_iSetBombPositionY[2] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[3] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[3] = DumpPosition;
		m_iSetBombPositionY[3] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[4] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[4] = DumpPosition;
		m_iSetBombPositionY[4] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[5] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[5] = DumpPosition;
		m_iSetBombPositionY[5] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[6] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[6] = DumpPosition;
		m_iSetBombPositionY[6] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[7] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[7] = DumpPosition;
		m_iSetBombPositionY[7] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[8] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[8] = DumpPosition;
		m_iSetBombPositionY[8] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
	if (m_iBombTimer[9] + 4000 < SDL_GetTicks())
	{
		m_iSetBombPositionX[9] = DumpPosition;
		m_iSetBombPositionY[9] = DumpPosition;
		m_pxInputmanager->SetActiveBombAmount();
	}
}

void GameState::DrawBombs()
{
	int o = 0;
	auto it = m_apxBomb.begin();
	while (it != m_apxBomb.end())
	{
		m_xSystem.m_pxDrawManager->Draw((*it)->GetSprite(), m_iSetBombPositionX[o], m_iSetBombPositionY[o]);
		it++;
		o++;
	}
		


	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb0, m_iSetBombPositionX[0], m_iSetBombPositionY[0]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb1, m_iSetBombPositionX[1], m_iSetBombPositionY[1]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb2, m_iSetBombPositionX[2], m_iSetBombPositionY[2]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb3, m_iSetBombPositionX[3], m_iSetBombPositionY[3]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb4, m_iSetBombPositionX[4], m_iSetBombPositionY[4]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb5, m_iSetBombPositionX[5], m_iSetBombPositionY[5]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb6, m_iSetBombPositionX[6], m_iSetBombPositionY[6]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb7, m_iSetBombPositionX[7], m_iSetBombPositionY[7]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb8, m_iSetBombPositionX[8], m_iSetBombPositionY[8]);
	m_xSystem.m_pxDrawManager->Draw(m_pxAnimatedBomb9, m_iSetBombPositionX[9], m_iSetBombPositionY[9]);

}
