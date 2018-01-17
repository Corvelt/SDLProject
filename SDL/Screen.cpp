#include "Screen.h"

namespace cvt {
	Screen::Screen() : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_blurBuffer(NULL)
	{
	}

	bool Screen::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return false;
		}

		/*SDL_DisplayMode DM;
		SDL_GetDesktopDisplayMode(0,&DM);*/
		SCREEN_WIDTH = 800;
		SCREEN_HEIGHT = 600;
		//Initialize window, renderer and texture
		m_window = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			SDL_Quit();
			return false;
		}
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == NULL)
		{
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
		if (m_texture == NULL)
		{
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_blurBuffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		// Set each pixel to a particular color
		memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));
		memset(m_blurBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));

	/*	for (int i = 0; i < (SCREEN_HEIGHT*SCREEN_WIDTH); i++)
		{
			m_buffer[i] = 0x000000FF;
		}
		*/
		return true;
	}

	bool Screen::ProcessEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				return false;
			}
		}
		return true;
	}

	void Screen::SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
			return;

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		m_buffer[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::BoxBlur()
	{
		Uint32 *temp = m_buffer;
		m_buffer = m_blurBuffer;
		m_blurBuffer = temp;

		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
				int redTotal = 0;
				int greenTot = 0;
				int blueTot = 0;


				for (int row = -1; row <= 1; row++)
				{
					for (int col = -1; col <= 1; col++)
					{
						int curX = x + col;
						int curY = y + row;

						if (curX >= 0 && curX < SCREEN_WIDTH && curY >= 0 && curY < SCREEN_HEIGHT)
						{
							Uint32 color = m_blurBuffer[curY*SCREEN_WIDTH + curX];
							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							redTotal += red;
							greenTot += green;
							blueTot += blue;
						}
					}
				}

				Uint8 red = redTotal / 9;
				Uint8 green = greenTot / 9;
				Uint8 blue = blueTot / 9;

				SetPixel(x,y,red,green,blue);
			}
		}
	}

	void Screen::Update()
	{
		//Updating the info on the screen
		SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	/*void Screen::Clear()
	{
		memset(m_buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));
		memset(m_blurBuffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT * sizeof(Uint32));
	}*/

	void Screen::Close()
	{
		//Clearing out memory
		delete[] m_buffer;
		delete[] m_blurBuffer;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	Screen::~Screen()
	{
	}
}