#pragma once

// If we want to make more entity types we can keep adding it to this list, this is to distinguish what they really are if we
// store different class* that inherit from IEntity in an IEntity* vector for example.
enum EENTITYTYPE
{
	ENTITY_BRICK,
	ENTITY_FLOOR,
	ENTITY_PlAYER
};

class Sprite;
class Collider;

class IEntity
{
public:
	~IEntity() {};
	virtual void Update(float p_fDeltaTime) = 0;
	virtual Sprite* GetSprite() = 0; // Can return nullptr if there is no sprite
	virtual Collider* GetCollider() = 0;
	virtual float GetX() = 0;
	virtual float GetY() = 0;
	virtual bool IsVisible() = 0;
	virtual EENTITYTYPE GetType() = 0;
};
