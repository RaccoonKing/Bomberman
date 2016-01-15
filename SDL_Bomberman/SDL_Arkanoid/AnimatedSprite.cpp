#include "stdafx.h"
#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite(SDL_Texture* p_pxTexture) : Sprite(p_pxTexture)
{
	m_iIndex = 0;
	m_fCurrentDuration = 0.0f;
}

void AnimatedSprite::AddFrame(int p_iX, int p_iY,
	int p_iWidth, int p_iHeight, float p_fDuration)
{
	FrameData data;
	data.m_xRegion.x = p_iX;
	data.m_xRegion.y = p_iY;
	data.m_xRegion.w = p_iWidth;
	data.m_xRegion.h = p_iHeight;
	data.m_fDuration = p_fDuration;
	m_axFrames.push_back(data);
}

void AnimatedSprite::Update(float p_fDeltaTime)
{
	// We increase the current duration with deltatime, the time from last fram to this frame.
	m_fCurrentDuration += p_fDeltaTime;

	// Check if currentduration has passed our currents frames duration
	if (m_fCurrentDuration >= m_axFrames[m_iIndex].m_fDuration) 
	{
		// If the index is lower then the amount of frames counted as index (-1)
		// then we can increment the frame we will be drawing
		if (m_iIndex < m_axFrames.size()-1)
		{
			m_iIndex++;
		}
		else
		{
			// If not then the m_iIndex is on the last fram of the container and we
			// should wrap it around so we start from frame index 0 again
			m_iIndex = 0;
		}

		// Update the region we will be usings value to the current frames region
		// and reset the currentduration
		m_xRegion = m_axFrames[m_iIndex].m_xRegion;
		m_fCurrentDuration = 0.0f;
	}
}