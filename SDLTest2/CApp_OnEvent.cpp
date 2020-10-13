#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	if (Event->type == SDL_QUIT)
	{
		Running = false;
	}
	else if (Event->type == SDL_KEYDOWN)
	{
		switch (Event->key.keysym.sym)
		{
		case SDLK_UP:
			if (r <= 1.0)
			{
				r += 0.1;
			}
			break;
		case SDLK_DOWN:
			if (r >= 0.0)
			{
				r -= 0.1;
			}
			break;
		case SDLK_RIGHT:
			if (b <= 1.0)
			{
				b += 0.1;
			}
			break;
		case SDLK_LEFT:
			if (b >= 0.0)
			{
				b -= 0.1;
			}
			break;
		case SDLK_PERIOD:
			if (g <= 1.0)
			{
				g += 0.1;
			}
			break;
		case SDLK_COMMA:
			if (g >= 0.0)
			{
				g -= 0.1;
			}
			break;

		}
	}
}