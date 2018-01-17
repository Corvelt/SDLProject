#pragma once

namespace cvt {
	struct Particles
	{	
		double m_x;
		double m_y;
	private:
		double m_speed;
		double m_direction;

	public:
		Particles();
		void Update(int interval);
		~Particles();
	private:
		void Init();
	};

}