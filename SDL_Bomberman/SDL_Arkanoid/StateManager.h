#pragma once

class IState;

class StateManager
{
	// Friend classing engine so that Engine class can reach the private 
	// setstate method to set our initial state.
	friend class Engine; 
public:
	StateManager();
	~StateManager();
	bool Update();
	void Draw();
private:
	void SetState(IState* p_pxState);
	IState* m_pxCurrentState;
	int m_iLastTick;
};
