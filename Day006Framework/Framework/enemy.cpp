
#include "enemy.h";

#include "entity.h";


Enemy::Enemy(){
	//Entity::Entity();
	
}

Enemy::~Enemy() {

}

void Enemy::Process(float deltaTime) {
	Entity::Process(deltaTime);


	// Ex006.2: Boundary checking and position capping. 
}

void Enemy::SetPosition(float x, float y) {
	m_x = x;
	m_y = y;
}
