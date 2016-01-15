#pragma once

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	struct FrameData
	{
		SDL_Rect m_xRegion;
		float m_fDuration;
	};
	AnimatedSprite(SDL_Texture* p_pxTexture);

	void AddFrame(int p_iX, int p_iY,
		int p_iWidth, int p_iHeight, float p_fDuration);

	void Update(float p_fDeltaTime);
private:
	std::vector<FrameData> m_axFrames;
	int m_iIndex;
	float m_fCurrentDuration;
};