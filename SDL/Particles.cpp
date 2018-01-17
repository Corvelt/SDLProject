#define _USE_MATH_DEFINES

#include "Particles.h"
#include <stdlib.h>
#include <cmath>

namespace cvt {

	Particles::Particles():m_x(0), m_y(0)
	{		
		Init();
	}

	void Particles::Init()
	{
		m_x = 0;
		m_y = 0;
		m_direction = (2 * M_PI * rand()) / RAND_MAX;
		m_speed = (.04 * rand()) / RAND_MAX;

		m_speed *= m_speed;
	}

	void Particles::Update(int interval)
	{		
		m_direction += interval*.0004;
		double xSpeed = m_speed * cos(m_direction);
		double ySpeed = m_speed * sin(m_direction);

		m_x += xSpeed * interval;
		m_y += ySpeed * interval;

		if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
		{
			Init();
		}

		if (rand() < RAND_MAX / 100)
		{
			Init();
		}
	}

	Particles::~Particles()
	{
	}

}