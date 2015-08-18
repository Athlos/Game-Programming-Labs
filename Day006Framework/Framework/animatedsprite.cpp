// This includes:
#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
{
	//Sprite::Sprite();
	AddFrame(0);
	AddFrame(64);
	AddFrame(128);
	AddFrame(192);
	AddFrame(256);


}

AnimatedSprite::~AnimatedSprite()
{

}

Texture*
AnimatedSprite::GetTexture()
{
	return (m_pTexture);
}


bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	//Sprite::Initialise(Texture& texture);
	Sprite::Initialise(texture);


	StartAnimating();

	return (true);
}

void
AnimatedSprite::AddFrame(int x)
{
	// Ex007.1: Add the x coordinate to the frame coordinate container.
	m_totalFrames.push_back(x);
}

void
AnimatedSprite::Process(float deltaTime)
{
	// Ex007.1: If not paused...
	if (m_paused) {
		return;
	}
	// Ex007.1: Count the time elapsed.
	m_timeElapsed += deltaTime;
	// Ex007.1: If the time elapsed is greater than the frame speed.
	if (m_timeElapsed > m_frameSpeed) {
		
		

		//reset if its at max frames
		if (m_currentFrame >= m_totalFrames.size()-1) {
			//if looping set to 0
			if (m_loop) {
				m_currentFrame = 0;
			}
			else {
			//if not looping turn of animation
				m_animating = false;
			}
			
		}

		//if not at max frames add 1
		if (m_currentFrame < m_totalFrames.size() - 1) {
			m_currentFrame++;
		}


		m_timeElapsed = 0.0f;
	}


	
	// Ex007.1: Move to the next frame.
	// Ex007.1: Reset the time elapsed counter.

	// Ex007.1: If the current frame is greater than the number 
	//          of frames in this animation...
	// Ex007.1: Reset to the first frame.

	// Ex007.1: Stop the animation if it is not looping...
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// Ex007.1: Draw the particular frame into the backbuffer.
	
	backbuffer.DrawAnimatedSprite(*this, m_totalFrames[m_currentFrame]);
	//          What is the current frame's x coordinate?
	//          What is the frame width?
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}