#pragma once
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

struct GameObject {
	glm::vec2 position, velocity, acceleration;
	SDL_Texture* texture;

	GameObject()
	{
		position = velocity = acceleration = glm::vec2(0);
	}
};