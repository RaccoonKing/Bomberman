#include "stdafx.h"
#include "Bomb.h"
#include "Collider.h"
#include "Sprite.h"

Bomb::Bomb(Sprite * p_pxSprite, float p_fX, float p_fY, int p_iTicks)
{
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_iTicks = p_iTicks;
	m_pxCollider = new Collider(
		p_pxSprite->GetRegion()->w,
		p_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
	m_pxCollider->Refresh();
	m_iTicks = p_iTicks;
}

Bomb::~Bomb()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Bomb::Update(float p_fDeltaTime)
{

}

int Bomb::GetTick()
{
	return m_iTicks;
}

Sprite * Bomb::GetSprite()
{
	return m_pxSprite;
}

Collider * Bomb::GetCollider()
{
	return m_pxCollider;
}

float Bomb::GetX()
{
	return m_fX;
}

float Bomb::GetY()
{
	return m_fY;
}

bool Bomb::IsVisible()
{
	return m_bVisible;
}

EENTITYTYPE Bomb::GetType()
{
	return EENTITYTYPE();
}
