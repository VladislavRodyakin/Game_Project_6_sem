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

//void Component::draw(SDL_Renderer* renderer)
void Component::draw() {
    return; // TODO probably should add this only to component that are drawable
            // maybe do an interface segregation to component and componentDrawable
        // but then there is problem with Entity::draw
}



Entity::Entity(Manager& manager) : m_manager(manager)
{
}

//void Entity::update(SDL_Event* m_event){
void Entity::update(){
    for (auto& c : m_components) {
        //c->update(m_event);
        c->update();
    }
}

//void Entity::draw(SDL_Renderer* renderer) {
void Entity::draw() {
    for (auto& c : m_components) {
        //c->draw(renderer);
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


//void Manager::update(SDL_Event* m_event) {
void Manager::update() {
    for (auto& entity : m_entities) {
        //entity->update(m_event);
        entity->update();
    }
}

//void Manager::draw(SDL_Renderer* renderer) {
void Manager::draw() {
    for (auto& entity : m_entities) {
        //entity->draw(renderer);
        entity->draw();
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
