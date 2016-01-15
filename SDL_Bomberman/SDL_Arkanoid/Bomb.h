#pragma once

#include "IEntity.h"

class Bomb : public IEntity
{
public:
	Bomb(Sprite* p_pxSprite, float p_fX, float p_fY, int p_iTicks);
	~Bomb();
	void Update(float p_fDeltaTime);
	int GetTick();
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EENTITYTYPE GetType();

private:
	Sprite* m_pxSprite;
	Collider* m_pxCollider;
	float m_fX;
	float m_fY;
	int m_iTicks;
	bool m_bVisible;
};