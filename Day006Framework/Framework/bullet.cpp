
#include "bullet.h";

#include "entity.h";


Bullet::Bullet(){
	Entity::Entity();

}

Bullet::~Bullet() {

}

void Bullet::Process(float deltaTime) {
	Entity::Process(deltaTime);

}

void Bullet::SetPosition(float x, float y) {
	m_x = x;
	m_y = y;
}

bool Bullet::IsOutOfBounds() {

	if (m_y < 0) {
		return true;
	}

	return false;
}