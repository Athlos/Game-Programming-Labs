// 717310 C++ SDL Framework

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <SDL.h>


// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "PlayerShip.h"

// Library includes:
#include <cassert>
#include <SDL.h>


Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_dead(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

bool Entity::IsDead() const{
	return m_dead;
}

void 
Entity::Process(float deltaTime)
{
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));

	// Ex006.2: Generic position update, based upon velocity (and time).
	m_x += deltaTime * m_velocityX;
	m_y += deltaTime * m_velocityY;
	
	// Ex006.2: Boundary checking and position capping. 
	if (m_x >= 800-m_pSprite->GetWidth()) {
		m_x = (800-m_pSprite->GetWidth());
		m_velocityX = 0;
	}
	if (m_x <= 0) {
		m_x = 0;
		m_velocityX = 0;
	}
}

void 
Entity::Draw(BackBuffer& backBuffer)
{

	assert(m_pSprite);
	m_pSprite->Draw(backBuffer);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// Ex006.4: Generic Entity Collision routine.

	// Ex006.4: Does this object collide with the e object?
	// Ex006.4: Create a circle for each entity (this and e).

	// Ex006.4: Check for intersection.
	// Ex006.4: Using circle-vs-circle collision detection.

	// Ex006.4: Return result of collision.

	int x1 = e.GetPositionX() + 8;
	int y1 = e.GetPositionY() + 8;
	int radius1 = 16;
	int radius2 = 16;

	//compare the distance to combined radii
	if (sqrt((x1 - m_x) * (x1 - m_x) + (y1 - m_y) * (y1 - m_y)) < 32)
	{
		return true;
		//Console.WriteLine("The 2 circles are colliding!");
	}

	//if (sqrt(pow((x1 - m_x), 2) + pow((y1 - m_y), 2) < 32))
	//sqrt((x2 – x1) ^ 2 + (y2 – y1) ^ 2) – r1 – r2
	float t = sqrt(pow((x1 - m_x), 2) + pow((y1 - m_x), 2) - 1 - 1);
	if (t <= 0) {
		//return true;
	}

	return (false); // Ex006.4 Change return value!
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

float 
Entity::GetPositionX()
{
	return (m_x);
}

float 
Entity::GetPositionY()
{
	return (m_y);
}

float 
Entity::GetHorizontalVelocity()
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity()
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}
