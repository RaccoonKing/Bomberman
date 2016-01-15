#pragma once

class Keyboard;

class InputManager
{
public:
	InputManager();
	~InputManager();
	void HandleKeyEvents();
	int GetSpeedX();
	int GetSpeedY();
	bool CheckQuit();
	bool CheckBomb();
	int CheckLayBomb();
	void SetActiveBombAmount();

private:
	void AddBombAmount();
	bool PlaceBomb = false;
	int m_iActiveBombAmount;
	int m_iAllowedBombAmount;
	int m_bLayBomb;
	bool m_bQuit;
	int m_iXS;
	int m_iYS;
	Keyboard* m_pxKeyboard;
};