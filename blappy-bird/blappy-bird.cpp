// blappy-bird.cpp : Defines the entry point for the application.
//

#include "blappy-bird.h"
#include <SDL3/SDL.h>

using namespace std;

void initialize();
int main()
{
	cout << "Hello CMake." << endl;

	initialize();

	SDL_Quit();
	return 0;
}

void initialize()
{
	// initialize SDL w/ video
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(2, "Error initializing window");
	}
	
	// create the window
	SDL_Window* window;
	window = SDL_CreateWindow(
		"Blappy Bird",
		640,
		480,
		SDL_WINDOW_OPENGL
	);
}
