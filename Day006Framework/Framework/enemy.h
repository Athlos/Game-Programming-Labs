#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();
	void Enemy::SetPosition(float x, float y);
	void Process(float deltaTime);
protected:
private:

};
#endif //__ENEMY_H__

