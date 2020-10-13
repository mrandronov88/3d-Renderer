#include "CApp.h"

void CApp::OnCleanup()
{

	SDL_GL_DeleteContext(mainContext);

	SDL_DestroyWindow(window);

	SDL_Quit();
}