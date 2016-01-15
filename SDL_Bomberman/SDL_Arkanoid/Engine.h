#pragma once

class DrawManager;
class SpriteManager;
class StateManager;
class InputManager;

class Engine
{
public:
	Engine();
	~Engine();

	/**
	* Initializes SDL and creates all Managers
	*/
	bool Initialize();

	/**
	* Quits SDL and deletes all Managers
	*/
	void Shutdown();

	/**
	* The Engines update loop
	*/
	void Update();
	void HandleEvents();

private:
	bool m_bRunning = false;
	DrawManager* m_pxDrawManager;
	SpriteManager* m_pxSpriteManager;
	StateManager* m_pxStateManager;
	InputManager* m_pxInputManager;

};

