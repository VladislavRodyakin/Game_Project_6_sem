#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <array>
#include <bitset>

class Component;
class Entity;
class Manager;
	
using ComponentID = std::size_t;
constexpr std::size_t maxComponents = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

class Component {
protected:
	Entity* m_entity;
public:
	Entity* getEntity();
	void setEntity(Entity* entity);

	virtual void init() = 0;
	//virtual void update(SDL_Event* m_event) = 0;
	virtual void update() = 0;
	virtual void draw(SDL_Renderer* renderer);
	virtual ~Component() {};
};

class Entity {
protected:
	bool m_active = true;
	std::vector<std::unique_ptr<Component>> m_components;
	ComponentArray m_componentArray;
	ComponentBitSet m_componentBitSet;
public:
	//void update(SDL_Event* m_event);
	void update();
	void draw(SDL_Renderer* renderer);
	bool isActive() const;
	void destroy();


	template<typename T> bool hasComponent() const {
		return m_componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
		T* comp(new T(std::forward<TArgs>(mArgs)...));
		comp->setEntity(this);

		std::unique_ptr<Component> uPtr{ comp };
		m_components.emplace_back(std::move(uPtr));
		m_componentArray[getComponentTypeID<T>()] = comp;
		m_componentBitSet[getComponentTypeID<T>()] = true;
		comp->init();
		return *comp;
	}

	template<typename T> T& getComponent() const {
		auto ptr(m_componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};


class Manager {
protected:
	std::vector<std::unique_ptr<Entity>> m_entities;
public:
	//void update(SDL_Event* m_event);
	void update();
	void draw(SDL_Renderer* renderer);
	void refresh();
	Entity& addEntity();
};
