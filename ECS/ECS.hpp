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
using Group = std::size_t;

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

inline ComponentID getNewComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

class Component {
protected:
	Entity* m_entity = nullptr;
public:
	Entity* getEntity();
	void setEntity(Entity* entity);

	virtual ~Component();
	//redo as interfaces
	//have to think how to do this

	virtual void init();
	virtual void update();
	virtual void draw();

};

class Entity {
protected:
	Manager& m_manager;
	bool m_active = true;
	std::vector<std::unique_ptr<Component>> m_components = {};
	ComponentArray m_componentArray = {};
	ComponentBitSet m_componentBitSet = {};
	GroupBitSet m_groupBitSet = {};

public:
	Entity(Manager& manager);

	void update();
	void draw();
	bool isActive() const;
	void destroy();

	bool hasGroup(Group group);
	void addGroup(Group group);
	void delGroup(Group group);


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
	std::vector<std::unique_ptr<Entity>> m_entities = {};
	std::array<std::vector<Entity*>, maxGroups> m_groupedEntities = {};
public:
	void update();
	void draw();
	void draw(std::vector<std::vector<Entity*>> groups);
	void refresh();

	void addToGroup(Entity* entity, Group group);
	std::vector<Entity*>& getGroup(Group group);

	Entity& addEntity();
};
