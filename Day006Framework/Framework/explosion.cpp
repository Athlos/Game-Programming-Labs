
#include "explosion.h"
#include "backbuffer.h"
#include "animatedsprite.h"
#include <cassert>

Explosion::Explosion(){
	Entity::Entity();
	
}

Explosion::~Explosion(){

}


void
Explosion::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->SetFrameSpeed(0.08f);
	m_pSprite->Process(deltaTime);
	if (!m_pSprite->IsAnimating()) {
		m_dead = true;
	}
}

bool
Explosion::Initialise(AnimatedSprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

void Explosion::Draw(BackBuffer& backBuffer)
{
	//Entity::Draw(backBuffer);
	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

void Explosion::SetPosition(float x, float y) {
	m_x = x;
	m_y = y;
}
