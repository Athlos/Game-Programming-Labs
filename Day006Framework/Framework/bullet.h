#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();
	void Process(float deltaTime);
	void Bullet::SetPosition(float x, float y);
	bool Bullet::IsOutOfBounds();
protected:
private:

};
#endif //__BULLET_H__

