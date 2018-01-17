#include "Swarm.h"

namespace cvt {

	Swarm::Swarm(): _lastTime(0)
	{
		m_particles = new Particles[NPARTICLES];
	}

	void Swarm::Update(int elapsed)
	{
		int interval = elapsed - _lastTime;

		for (int i = 0; i < NPARTICLES; i++)
		{
			m_particles[i].Update(interval);
		}
		_lastTime = elapsed;
	}


	Swarm::~Swarm()
	{
		delete [] m_particles;
	}
}