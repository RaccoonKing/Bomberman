#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include <math.h>

bool CollisionManager::Check(Collider* p_pxLeft, Collider* p_pxRight,
								int& p_iOverlapX, int& p_iOverlapY)
{
	p_iOverlapX = 0;
	p_iOverlapY = 0;
	// Separated Axis Theorem
	int iLeftCenterX = p_pxLeft->GetX() + p_pxLeft->GetW() / 2; // Calculate center position left X
	int iLeftCenterY = p_pxLeft->GetY() + p_pxLeft->GetH() / 2; // Calculate center position left y
	int iRightCenterX = p_pxRight->GetX() + p_pxRight->GetW() / 2; // Calculate center position right x
	int iRightCenterY = p_pxRight->GetY() + p_pxRight->GetH() / 2; // Calculate center position right y
	int iCenterDeltaX = iLeftCenterX - iRightCenterX; // Distance between center X left and right
	int iCenterDeltaY = iLeftCenterY - iRightCenterY; // Distance between center Y left and right

	// If distance between the rectangles center in X axis is LESS then their half their combined WIDTH they are overlapping in X axis. 
	if (abs(iCenterDeltaX) < (p_pxLeft->GetW() / 2 + p_pxRight->GetW() / 2)) 
	{
		// If distance between the rectangles center in Y axis is LESS then their half their combined HEIGHT they are overlapping in Y axis. 
		if (abs(iCenterDeltaY) < (p_pxLeft->GetH() / 2 + p_pxRight->GetH() / 2))
		{
			int iDeltaX = (p_pxLeft->GetW()/2 + p_pxRight->GetW()/2) - abs(iCenterDeltaX);
			int iDeltaY = (p_pxLeft->GetH()/2 + p_pxRight->GetH()/2) - abs(iCenterDeltaY);

			// Find the smallest overlap and return that information in the ints passed as reference
			if (iDeltaY < iDeltaX)
			{
				p_iOverlapY = iDeltaY;
				if (iCenterDeltaY < 0)
					p_iOverlapY = -p_iOverlapY;
			}
			else if (iDeltaY > iDeltaX)
			{
				p_iOverlapX = iDeltaX;
				if (iCenterDeltaX < 0)
					p_iOverlapX = -p_iOverlapX;
			}
			else
			{
				if (iCenterDeltaX < 0)
					p_iOverlapX = -iDeltaX;
				else
					p_iOverlapX = iDeltaX;


				if (iCenterDeltaY < 0)
					p_iOverlapY = -iDeltaY;
				else
					p_iOverlapY = iDeltaY;

			}
			return true;
		}
	}

	return false;
}