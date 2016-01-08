#pragma once

#include "IEntity.h"

class Brick : public IEntity
{
public:
	Brick(Sprite* p_pxSprite, float p_fX, float p_fY);
	~Brick();
	void Update(float p_fDeltaTime);
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
	bool m_bVisible;
	
};