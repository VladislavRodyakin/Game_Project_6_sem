#pragma once
#include "SDL.h"
#include "ECS/ColliderComponent.hpp"

namespace Collision {
	bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
	bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};