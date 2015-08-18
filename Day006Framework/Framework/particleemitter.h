#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "particle.h"
#include <vector>

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
protected:
private:

	//Member Data:
public:
protected:
	std::vector<Particle> m_particles;
private:

};
#endif //__PARTICLEEMITTER_H__