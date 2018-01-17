#include <SDL.h>
#include <iostream>>

namespace cvt {

	class Screen
	{
	public:
		/*const static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;*/

		int SCREEN_WIDTH = 0;
		int SCREEN_HEIGHT = 0;

		Screen();
		bool Init();
		bool ProcessEvents();
		void Close();
		void SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void BoxBlur();
		void Update();
		//void Clear();
		~Screen();

	private:
		SDL_Window *m_window;
		SDL_Renderer *m_renderer;
		SDL_Texture *m_texture;
		Uint32 *m_buffer;
		Uint32 *m_blurBuffer;

	};

}