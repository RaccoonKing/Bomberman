#include "stdafx.h"
#include "Engine.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "CollisionManager.h"
#include "StateManager.h"
#include "InputManager.h"
#include "IState.h"
#include "GameState.h"
#include "Keyboard.h"

const int SCREENWIDTH = 800;
const int SCREEHEIGHT = 600;

Engine::Engine()
{
	m_bRunning = false;
	m_pxDrawManager = nullptr;
	m_pxSpriteManager = nullptr;
	m_pxStateManager = nullptr;
	m_pxInputManager = nullptr;
}

Engine::~Engine()
{

}


bool Engine::Initialize()
{
	// The initialize function will intialize libraries the program depends on and all manager we will create.
	 
	// Initializes the SDL library
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	// Creates a new DrawManager and calls Initialize with width / height parameters.
	m_pxDrawManager = new DrawManager();
	if (m_pxDrawManager->Initialize(SCREENWIDTH, SCREEHEIGHT) == false)
	{
		return false;
	}

	m_pxSpriteManager = new SpriteManager(m_pxDrawManager->GetRenderer());

	m_pxStateManager = new StateManager();

	System system;
	system.m_iScreenWidth = SCREENWIDTH;
	system.m_iScreenHeight = SCREEHEIGHT;
	system.m_pxDrawManager = m_pxDrawManager;
	system.m_pxSpriteManager = m_pxSpriteManager;

	m_pxStateManager->SetState(new GameState(system));

	m_bRunning = true;

	return true;
}

void Engine::Shutdown()
{
	// The shutdown function will quit, delete and shutdown everything we have started up or created in initialize (In reverse order of creation)
	
	// Shuts down the drawmanager before deleting the object and nulling the pointer.
	delete m_pxInputManager;
	m_pxInputManager = nullptr;

	delete m_pxStateManager;
	m_pxStateManager = nullptr;

	delete m_pxSpriteManager;
	m_pxSpriteManager = nullptr;
	
	m_pxDrawManager->Shutdown();

	delete m_pxDrawManager;
	m_pxDrawManager = nullptr;

	SDL_Quit();
}

void Engine::Update()
{
	/* TEMP CODE TO TEST RENDERING
	SDL_Surface* xSurface = SDL_LoadBMP("../assets/Template.bmp");
	SDL_Texture* xTexture = SDL_CreateTextureFromSurface(m_pxDrawManager->GetRenderer(),xSurface);
	SDL_FreeSurface(xSurface);
	Sprite* xSprite = new Sprite(xTexture, 40,0,40,40);
	/* TEMP CODE TO TEST RENDERING*/


	// Our engines core loop
	while (m_bRunning)
	{
		HandleEvents();
		m_pxDrawManager->Clear();
		if (m_pxStateManager->Update() == false)
		{
			m_bRunning = false;
		}
		m_pxStateManager->Draw();
		m_pxDrawManager->Present();
		SDL_Delay(10);
	}

}

void Engine::HandleEvents()
{
	SDL_Event xEvent;    

	while (SDL_PollEvent(&xEvent))   
	{
		if (xEvent.type == SDL_QUIT)
		{
			m_bRunning = false;
		}
		else
		{
			m_pxInputManager->HandleKeyEvents();
		}
	}
}