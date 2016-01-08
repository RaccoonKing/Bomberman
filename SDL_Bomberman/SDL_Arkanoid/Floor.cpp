#include "stdafx.h"
#include "Floor.h"
#include "Collider.h"
#include "Sprite.h"

Floor::Floor(Sprite* p_pxSprite,
	float p_fX, float p_fY)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	
}

Floor::~Floor()
{

}

void Floor::Update(float p_fDeltaTime)
{
}

Sprite* Floor::GetSprite()
{
	return m_pxSprite;
}

Collider * Floor::GetCollider()
{
	return nullptr;
}


float Floor::GetX()
{
	return m_fX;
}

float Floor::GetY()
{
	return m_fY;
}

bool Floor::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Floor::GetType()
{
	return EENTITYTYPE::ENTITY_FLOOR;
}