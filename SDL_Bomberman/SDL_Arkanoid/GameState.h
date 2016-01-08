#pragma once

#include "IState.h"
class Brick;
class Floor;
class Player;


class GameState : public IState
{
public:
	GameState(System& p_xSystem);
	~GameState();
	void Enter();
	void Exit();
	bool Update(float p_fDeltaTime);
	void Draw();
	IState* NextState();
private:
	void CheckCollision();
	void EnterWalls();
	void EnterFloor();
	System m_xSystem;
	Player* m_pxPlayer;
	std::vector<Brick*> m_apxBricks;
	std::vector<Floor*> m_apxFloor;

};
