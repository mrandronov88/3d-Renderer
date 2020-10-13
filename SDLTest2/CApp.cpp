#include "CApp.h"
#include <iostream>


CApp::CApp()
{
	window = NULL;

	Running = true;
}

int CApp::OnExecute()
{
	if ( OnInit() == false )
	{
		return -1;
	}

	//shader.init();

	SDL_Event Event;

	while ( Running)
	{
		while ( SDL_PollEvent(&Event) )
		{
			OnEvent( &Event );
		}

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;
}

int main(int argc, char* argv[])
{
	CApp theApp;
	std::cout << "Hello world.\n";
	return theApp.OnExecute();
}