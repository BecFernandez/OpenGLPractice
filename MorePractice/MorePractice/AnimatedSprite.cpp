#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const glm::vec3 a_position,
		const glm::vec4 a_colour,
		const unsigned int a_uiWidth, const unsigned int a_uiHeight, const char* a_szTexName,
		const int a_iNumRows, const int a_iNumCols, const int a_iFrameWidth, const int a_iFrameHeight, 
		const float a_fTimer, const bool a_bLooping) :
		Sprite(a_position, a_colour, a_uiWidth, a_uiHeight, a_szTexName),
			m_iNumRows(a_iNumRows), m_iNumCols(a_iNumCols), m_iFrameWidth(a_iFrameWidth), m_iFrameHeight(a_iFrameHeight),
			m_fTimer(a_fTimer), m_bLooping(a_bLooping), m_fTimePerFrame(a_fTimer/(m_iNumRows*m_iNumCols)), 
			m_fCurrentTime(0), m_bStillRunning(true), m_iCurrentFrame(0)
		{
			Sprite::setSpriteUVCoords((1.0*(m_iCurrentFrame%m_iNumCols))/m_iNumCols, (1.0*(m_iCurrentFrame%m_iNumRows))/m_iNumRows,
			(1.0*(m_iCurrentFrame%m_iNumCols + 1))/m_iNumCols, (1.0*(m_iCurrentFrame%m_iNumRows + 1))/m_iNumRows);
		}

void AnimatedSprite::Update(const double a_dDeltaTime)
{
	//add to sprite timer
	m_fCurrentTime += a_dDeltaTime;
	//if timer goes past certain value
	if(m_fCurrentTime >= m_fTimePerFrame)
	{
		//to ensure animation plays at the correct speed - excess time carries over into next frame
		while(m_fCurrentTime >= m_fTimePerFrame)
		{
			m_fCurrentTime -= m_fTimePerFrame;
		}
		//move to next frame
		m_iCurrentFrame++;
		if(m_iCurrentFrame >= m_iNumCols * m_iNumRows)
		{
			if(m_bLooping)
				m_iCurrentFrame = 0;
			else
				m_bStillRunning = false;
		}
	
		//update UVs
		Sprite::setSpriteUVCoords((1.0*(m_iCurrentFrame%m_iNumCols))/m_iNumCols, (1.0*(m_iCurrentFrame/m_iNumRows))/m_iNumRows,
			(1.0*(m_iCurrentFrame%m_iNumCols + 1))/m_iNumCols, (1.0*(m_iCurrentFrame/m_iNumRows + 1))/m_iNumRows);
	}
	Sprite::Update(a_dDeltaTime);
}