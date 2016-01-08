#pragma once


class InputManager
{
public:
	InputManager();
	~InputManager();
	void HandleKeyEvents();
	int GetSpeedX();
	int GetSpeedY();

private:
	int m_iXS;
	int m_iYS;
};