// 717310 C++ SDL Framework
#ifndef __PLAYERSHIP_H__
#define __PLAYERSHIP_H__


#include "entity.h";


class PlayerShip : public Entity
{
	//Member Methods:
public:
	PlayerShip();
	~PlayerShip();
	void Process(float deltaTime);
	void setHorizontalVelocity(float move);
protected:

private:
	


};

#endif //__PLAYERSHIP_H__
