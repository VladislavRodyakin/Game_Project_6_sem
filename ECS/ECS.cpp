#include "ECS.hpp"

Entity* Component::getEntity(){
    return m_entity;
}

void Component::setEntity(Entity* entity){
    m_entity = entity;
}

Component::~Component() {
}

void Component::init() {
    return;
}

void Component::update() {
    return;
}

void Component::draw() {
    return; 
}



Entity::Entity(Manager& manager) : m_manager(manager)
{
}

void Entity::update(){
    for (auto& c : m_components) {
        c->update();
    }
}

void Entity::draw() {
    for (auto& c : m_components) {
        c->draw();
    }
};

bool Entity::isActive() const {
    return m_active;
}

void Entity::destroy() {
    m_active = false;
}

bool Entity::hasGroup(Group group) {
    return m_groupBitSet[group];
}

void Entity::addGroup(Group group) {
    m_groupBitSet[group] = true;
    m_manager.addToGroup(this, group);
}

void Entity::delGroup(Group group) {
    m_groupBitSet[group] = false;
}


void Manager::update() {
    for (auto& entity : m_entities) {
        entity->update();
    }
}

void Manager::draw() {
    for (auto& entity : m_entities) {
        entity->draw();
    }
}

void Manager::draw(std::vector<std::vector<Entity*>> groups) {
    for (auto& group : groups) {
        for (auto& entity : group) {
            entity->draw();
        }
    }
}

void Manager::refresh() {
    for (auto i(0u); i < maxGroups; i++) {
        auto& vec(m_groupedEntities[i]);
        vec.erase(std::remove_if(std::begin(vec), std::end(vec),
            [i](Entity* entity) {
                return !entity->isActive() || !entity->hasGroup(i); 
            }
            ), std::end(vec));
    }
    m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
        [](const std::unique_ptr<Entity>& mEntity) { return !mEntity->isActive(); }),
        std::end(m_entities));
}

void Manager::addToGroup(Entity* entity, Group group) {
    m_groupedEntities[group].emplace_back(entity);
}

std::vector<Entity*>& Manager::getGroup(Group group)
{
    return m_groupedEntities[group];
}

Entity& Manager::addEntity() {
    Entity* entity = new Entity(*this);
    std::unique_ptr<Entity> entityPtr{ entity };
    m_entities.emplace_back(std::move(entityPtr));
    return *entity;
}
