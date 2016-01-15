#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Collider.h"

Player::Player(InputManager * p_pxInputManager, Sprite * p_pxSprite, float p_fX, float p_fY)
{
	m_pxInputManager = p_pxInputManager;
	m_pxSprite = p_pxSprite;
	m_fX = p_fX;
	m_fY = p_fY;
	m_bVisible = true;
	m_pxCollider = new Collider(
		m_pxSprite->GetRegion()->w,
		m_pxSprite->GetRegion()->h);
	m_pxCollider->SetParent(this);
}

Player::~Player()
{
	delete m_pxCollider;
	m_pxCollider = nullptr;
}

void Player::Update(float p_fDeltaTime)
{
	m_fX = m_fX + m_pxInputManager->GetSpeedX();
	m_fY = m_fY + m_pxInputManager->GetSpeedY();
	m_pxCollider->Refresh();
}

Sprite * Player::GetSprite()
{
	return m_pxSprite;
}

Collider * Player::GetCollider()
{
	return m_pxCollider;
}

float Player::GetX() { return m_fX; }

float Player::GetY() { return m_fY; }

bool Player::IsVisible() { return m_bVisible; }

int Player::GetSpeedX()
{
	return m_pxInputManager->GetSpeedX();
}

int Player::GetSpeedY()
{
	return m_pxInputManager->GetSpeedY();
}

void Player::SetPosition(float p_fX, float p_fY)
{
	m_fX = p_fX;
	m_fY = p_fY;
}

EENTITYTYPE Player::GetType() { return EENTITYTYPE::ENTITY_PlAYER; }
