#pragma once

#include "IEntity.h"
#include "Sprite.h"
class InputManager;


class Player : public IEntity
{
public:
	Player(InputManager* p_pxInputManager, Sprite* p_pxSprite, float p_fX, float p_fY);
	~Player();
	void Update(float p_fDeltaTime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	int GetSpeedX();
	int GetSpeedY();
	void SetPosition(float p_fX, float p_fY);
	EENTITYTYPE GetType();

private:
	Player() {};
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	InputManager* m_pxInputManager;
	float m_fX;
	float m_fY;
	bool m_bVisible;

};