#include "UILabel.hpp"

UILabel::UILabel(int xpos, int ypos, std::string text, std::string font, const SDL_Color& color, SDL_Renderer* renderer) :
m_text(text), m_font(font), m_text_color(color), m_renderer(renderer) {
	m_position.x = xpos;
	m_position.y = ypos;
	SetLabelText(m_text);
}

UILabel::~UILabel() {
}

void UILabel::SetLabelText(std::string text) {
	m_text = text;
	SDL_Surface* tmp_surface = TTF_RenderText_Blended(Game::m_asset_manager.GetFont(m_font), m_text.c_str(), m_text_color);
	m_texture = SDL_CreateTextureFromSurface(m_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_position.w, &m_position.h);
}

void UILabel::draw() {
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_position);
}
