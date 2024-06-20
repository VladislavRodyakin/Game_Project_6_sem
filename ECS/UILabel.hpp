#pragma once
#include "ECS.hpp"
#include "Components.hpp"
#include "../AssetManager.hpp"
#include "../Game.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UILabel : public Component {
	SDL_Rect m_position = { 0,0,0,0 };
	std::string m_text = "";
	std::string m_font = "";
	SDL_Color m_text_color = { 0,0,0,0 };
	SDL_Texture* m_texture = nullptr;
	SDL_Renderer* m_renderer = nullptr;
public:
	UILabel(int xpos, int ypos, std::string text, std::string font, const SDL_Color& color, SDL_Renderer* renderer);
	~UILabel();

	void SetLabelText(std::string text);
	void draw() override;
};