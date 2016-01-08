#pragma once

class SpriteManager;
class DrawManager;
class InputManager;


// A struct that we create in the Engine so we can send important pointers
// to potential future states for them to use.
struct System
{
	int m_iScreenWidth;
	int m_iScreenHeight;
	SpriteManager* m_pxSpriteManager;
	DrawManager* m_pxDrawManager;
	InputManager* m_pxInputManager;
};

// Interface class, incomplete class with pure virtual functions that need to be
// both declared and defines in derived classes. Only virtual will give the option
// to declare and define the function while pure virtual forces it.
class IState
{
public:
	virtual ~IState() {};
	virtual void Enter() {};
	virtual bool Update(float p_fDeltaTime) = 0;
	virtual void Exit() {};
	virtual void Draw() = 0;
	virtual IState* NextState() = 0;
};