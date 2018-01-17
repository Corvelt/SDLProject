
#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"
using namespace std;
using namespace cvt;


int main(int argc, char* args[])
{
	//Seed random number with time to get different numbers
	srand(time(NULL));

	// Create screen and initialize
	Screen screen;
	if (screen.Init() == false)
	{
		cout << "Error initializing screen" << endl;
	}
	int max = 0;

	//Create a swarm of particles
	Swarm swarm;

	//Game loop
	while (true)
	{
		int elapsed = SDL_GetTicks();	
		
		//Update the positions of the particles in swarm
		swarm.Update(elapsed);

		//Create the colors to apply to the particles
		unsigned char green = (unsigned char)((1 + sin(elapsed * .0001)) * 128);
		unsigned char red = (unsigned char)((1 + sin(elapsed * .0005)) * 128);
		unsigned char blue = (unsigned char)((1 + sin(elapsed * .001)) * 128);

		// Make each particle the color and set the pixel to it
		const Particles * const pParticles = swarm.GetParticles();
		for (int i = 0; i < swarm.NPARTICLES; i++)
		{
			Particles particle = pParticles[i];

			int x = (particle.m_x + 1) * screen.SCREEN_WIDTH / 2;
			int y = particle.m_y  * screen.SCREEN_WIDTH / 2 +(screen.SCREEN_HEIGHT/2);
			screen.SetPixel(x, y, red, green, blue);
		}			

		// Bluring the pixels
		screen.BoxBlur();

		//Draw the screen
		screen.Update();

		//Checks for Messages and events
		if (!screen.ProcessEvents())
		{
			break;
		}
	}

	//Call to clean memory
	screen.Close();
	return 0;
}