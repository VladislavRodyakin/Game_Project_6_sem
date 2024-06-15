#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(std::string texture_img_path, SDL_Renderer* renderer,
					int xpos, int ypos): m_renderer(renderer), 
					m_xpos(xpos), m_ypos(ypos)
{
	m_obj_texture = TextureManager::LoadTexture(texture_img_path, m_renderer);
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	m_xpos++;
	m_ypos++;
	
	m_src_R.h = TextureManager::h_texture_dimension;
	m_src_R.w = TextureManager::w_texture_dimension;
	m_src_R.x = 0;
	m_src_R.y = 0;
	
	//m_dst_R.h = m_src_R.h * 2;
	//m_dst_R.w = m_src_R.w * 2;
	m_dst_R.h = m_src_R.h;
	m_dst_R.w = m_src_R.w;
	m_dst_R.x = m_xpos;
	m_dst_R.y = m_ypos;

}

void GameObject::render()
{
	SDL_RenderCopy(m_renderer, m_obj_texture, &m_src_R, &m_dst_R);
}
