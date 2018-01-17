#pragma once
#include "Particles.h"

namespace cvt {
	class Swarm
	{
	public:
		const static int NPARTICLES = 4000;
	private:
		int _lastTime;
		Particles *m_particles;
	public:
		Swarm();
		const Particles * const GetParticles() { return  m_particles; }
		void Update(int elapsed);
		~Swarm();
	};
}
