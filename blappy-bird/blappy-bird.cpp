// blappy-bird.cpp : Defines the entry point for the application.
//

#include "blappy-bird.h"
#include <SDL3/SDL.h>

using namespace std;

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width = 1280;
	int height = 720;
};

void initialize(SDLState& state);

int main()
{
	cout << "Hello CMake." << endl;

	// initialize SDL video, create window
	SDLState state;
	initialize(state);

	// game loop
	bool gameRunning = true;
	while (gameRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
					gameRunning = false;
					break;
			}
		}
	}

	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
	return 0;
}

void initialize(SDLState& state)
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
		state.width,
		state.height,
		SDL_WINDOW_OPENGL
	);
	state.window = window;

	// create renderer
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, NULL);
	state.renderer = renderer;
}
