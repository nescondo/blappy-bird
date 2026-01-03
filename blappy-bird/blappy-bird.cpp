// blappy-bird.cpp : Defines the entry point for the application.
//

#include "blappy-bird.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include "gameobject.h"
#include <glm/glm.hpp>

using namespace std;

struct SDLState {
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width = 1280;
	int height = 720;
	const bool* keys; // holds keyboard state

	// default constructor initializes 'keys' member var. w/ snapshot of keyboard state
	SDLState() : keys(SDL_GetKeyboardState(nullptr))
	{
	}
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
void handleKeyInput(SDLState& state, GameObject& obj, SDL_Keycode key, bool keyDown);

int main(int argc, char *argv[])
{
	cout << "Hello CMake." << endl;

	// initialize SDL video, create window
	SDLState state;
	initialize(state);

	// initialize game resources
	Resources res;
	res.load(state);

	// create player object
	GameObject player;
	player.position = glm::vec2(
		0, // horizontal position
		0); // vertical position
	player.texture = res.textures[0];
	player.acceleration = glm::vec2(10, 0);

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
				{
					gameRunning = false;
					break;
				}
				case SDL_EVENT_KEY_DOWN:
				{
					handleKeyInput(state, player, event.key.key, true);
					break;
				}
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

		// draw player texture
		SDL_FRect src{
			.x = 0,
			.y = 0,
			.w = static_cast<float>(player.texture->w),
			.h = static_cast<float>(player.texture->h)
		};

		SDL_FRect dst{
			.x = 200,
			.y = 300 + player.velocity.y,
			.w = static_cast<float>(player.texture->w),
			.h = static_cast<float>(player.texture->h)
		};

		SDL_RenderTexture(state.renderer, player.texture, &src, &dst);

		
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

void handleKeyInput(SDLState& state, GameObject& obj, SDL_Keycode key, bool keyDown)
{
	const float JUMP_FORCE = -10.0f;
	if (keyDown && key == SDLK_SPACE)
	{
		// TODO: this is for each frame, use delta time
		obj.velocity += obj.acceleration;
		obj.velocity.y += JUMP_FORCE;
		obj.position.y += obj.velocity.y;
		SDL_Log("space pressed");
	}
}
