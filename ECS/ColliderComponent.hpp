#pragma once
#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class ColliderComponent : public Component {
	SDL_Rect m_collider = { 0,0,0,0 };
	std::string m_tag = "";

	SDL_Texture* m_texture = nullptr;
	SDL_Rect m_src_r = { 0,0,0,0 }, m_dst_r = { 0,0,0,0 };
	SDL_Renderer* m_renderer = nullptr;

	TransformComponent *m_transform = nullptr;

public:
	ColliderComponent();
	ColliderComponent(std::string tag, SDL_Renderer* renderer);
	ColliderComponent(std::string tag, int xpos, int ypos, int size, SDL_Renderer* renderer);

	void init() override;
	void update() override;
	void draw() override;

	const SDL_Rect& getCollider() const;
	const std::string& getTag() const;
};