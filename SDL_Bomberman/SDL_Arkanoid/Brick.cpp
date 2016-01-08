#include "stdafx.h"
#include "Brick.h"
#include "Collider.h"
#include "Sprite.h"

Brick::Brick(Sprite* p_pxSprite,
	float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_pxCollider = new Collider(
		p_pxSprite->GetRegion()->w,
		p_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	m_pxCollider->Refresh();
}

Brick::~Brick()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Brick::Update(float p_fDeltaTime)
{
}

Sprite* Brick::GetSprite()
{
	return m_pxSprite;
}


Collider* Brick::GetCollider()
{
	return m_pxCollider;
}


float Brick::GetX()
{
	return m_fX;
}

float Brick::GetY()
{
	return m_fY;
}

bool Brick::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Brick::GetType()
{
	return EENTITYTYPE::ENTITY_BRICK;
}