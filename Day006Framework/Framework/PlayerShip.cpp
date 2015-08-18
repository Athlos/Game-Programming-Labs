

#include "PlayerShip.h";

#include "entity.h";
#include "sprite.h"
#include "backbuffer.h"


	PlayerShip::PlayerShip(){
		Entity::Entity();
		m_x = 800 / 2;
		m_y = 550;

	}


	PlayerShip::~PlayerShip() {

	}

	void PlayerShip::Process(float deltaTime) {
		Entity::Process(deltaTime);
		

		// Ex006.2: Boundary checking and position capping. 
	}

	void PlayerShip::setHorizontalVelocity(float move)
	{
		Entity::SetHorizontalVelocity(move);
	}
