#pragma once

class Collider;

class CollisionManager
{
public:
	// Static means the function belongs to the class and can be reached without having an
	// object of the type CollisionManager. To reach a class static method you write ClassType::StaticFunction(...)
	static bool Check(Collider* p_pxLeft, Collider* p_pxRight, int& p_iOverlapX, int& p_iOverlapY);
};