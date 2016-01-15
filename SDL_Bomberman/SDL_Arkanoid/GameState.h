#pragma once

#include "IState.h"
class Brick;
class Floor;
class Player;
class Brick;
class InputManager;
class AnimatedSprite;
class Bomb;


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
	int m_iSetBombPositionX[10];
	int m_iSetBombPositionY[10];
	int m_iBombDeployment;
	int m_iBombTimer[10];
	int m_iBT;
	int StillSprite;
	int DumpPosition;
	void CheckCollision();
	void EnterWalls();
	void EnterFloor();
	void EnterAnimatedSprites();
	void DrawPlayer();
	void EnterBombs();
	void CheckBombs();
	void DrawBombs();
	System m_xSystem;
	Player* m_pxPlayer;
	std::vector<Bomb*> m_apxBomb;
	Player* m_pxStillPlayerRight;
	Player* m_pxStillPlayerLeft;
	Player* m_pxStillPlayerUp;
	Player* m_pxStillPlayerDown;
	InputManager* m_pxInputmanager;
	std::vector<Brick*> m_apxBricks;
	std::vector<Floor*> m_apxFloor;
	AnimatedSprite* m_pxAnimatedSpriteRight;
	AnimatedSprite* m_pxAnimatedSpriteLeft;
	AnimatedSprite* m_pxAnimatedSpriteUp;
	AnimatedSprite* m_pxAnimatedSpriteDown;
	AnimatedSprite* m_pxAnimatedBomb0;
	AnimatedSprite* m_pxAnimatedBomb1;
	AnimatedSprite* m_pxAnimatedBomb2;
	AnimatedSprite* m_pxAnimatedBomb3;
	AnimatedSprite* m_pxAnimatedBomb4;
	AnimatedSprite* m_pxAnimatedBomb5;
	AnimatedSprite* m_pxAnimatedBomb6;
	AnimatedSprite* m_pxAnimatedBomb7;
	AnimatedSprite* m_pxAnimatedBomb8;
	AnimatedSprite* m_pxAnimatedBomb9;
};
