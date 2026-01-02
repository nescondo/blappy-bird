// blappy-bird.cpp : Defines the entry point for the application.
//

#include "blappy-bird.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>

using namespace std;

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width = 1280;
	int height = 720;
};

struct Resources {
	// player animations
	const int ANIM_PLAYER_IDLE = 0;
	const int ANIM_PLAYER_JUMP_START = 1;
	const int ANIM_PLAYER_END_START = 2;
	std::vector<int> playerAnims;

	// all textures
	std::vector<SDL_Texture*> textures;
	SDL_Texture *playerIdle, *playerStartJump, *playerEndJump;

	// load a single texture, set scaling, and push into textures vector
	SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filepath)
	{
		SDL_Texture* tex = IMG_LoadTexture(renderer, filepath.c_str());
		SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
		textures.push_back(tex);
		return tex;
	};

	// load all textures
	void load(SDLState& state)
	{
		playerIdle = loadTexture(state.renderer, "data/blappy/blappyIdle.png");
		playerStartJump = loadTexture(state.renderer, "data/blappy/blappyStartJump.png");
		playerEndJump = loadTexture(state.renderer, "data/blappy/blappyEndJump.png");
	};

	// unload all textures
	void unload(SDLState& state)
	{
		for (SDL_Texture* tex : textures)
		{
			SDL_DestroyTexture(tex);
		}
	};
};

void initialize(SDLState& state);
void cleanup(SDLState& state);

int main(int argc, char *argv[])
{
	cout << "Hello CMake." << endl;

	// initialize SDL video, create window
	SDLState state;
	initialize(state);

	// initialize game resources
	Resources res;
	res.load(state);

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

		// Set drawing commands and clear renderer
		SDL_SetRenderDrawColor(state.renderer, 0, 30, 0, 255);
		SDL_RenderClear(state.renderer);

		// load bird1.png texture
		/*const std::string& filepath = "data/blappy/blappyStartJump.png";
		SDL_Texture* blappy = IMG_LoadTexture(state.renderer, filepath.c_str());
		SDL_SetTextureScaleMode(blappy, SDL_SCALEMODE_NEAREST);

		SDL_RenderTexture(state.renderer, blappy, NULL, NULL);*/

		// load player textures
		SDL_RenderTexture(state.renderer, res.textures[0], NULL, NULL);

		
		// swap buffers and present new image
		SDL_RenderPresent(state.renderer);

	}

	// remember to destroy texture when done
	/* SDL_DestroyTexture(blappy); - can't right now */

	cleanup(state);
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
		SDL_WINDOW_RESIZABLE
	);
	state.window = window;

	// create renderer
	SDL_Renderer* renderer;
	renderer = SDL_CreateRenderer(window, NULL);
	state.renderer = renderer;
}

void cleanup(SDLState& state)
{
	// cleanup allocated memory
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
}
