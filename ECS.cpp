#include "ECS.hpp"

Entity* Component::getEntity(){
    return m_entity;
}

void Component::setEntity(Entity* entity){
    m_entity = entity;
}

void Component::draw(SDL_Renderer* renderer)
{
    return; // TODO probably should add this only to component that are drawable
            // maybe do an interface segregation to component and componentDrawable
        // but then there is problem with Entity::draw
}



//void Entity::update(SDL_Event* m_event){
void Entity::update(){
    for (auto& c : m_components) {
        //c->update(m_event);
        c->update();
    }
}

void Entity::draw(SDL_Renderer* renderer) {
    for (auto& c : m_components) {
        c->draw(renderer);
    }
};

bool Entity::isActive() const{
    return m_active;
}

void Entity::destroy(){
    m_active = false;
}

//void Manager::update(SDL_Event* m_event) {
void Manager::update() {
    for (auto& entity : m_entities) {
        //entity->update(m_event);
        entity->update();
    }
}

void Manager::draw(SDL_Renderer* renderer) {
    for (auto& entity : m_entities) {
        entity->draw(renderer);
    }
}

void Manager::refresh() {
    m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
        [](const std::unique_ptr<Entity>& mEntity) { return !mEntity->isActive(); }),
        std::end(m_entities));
}

Entity& Manager::addEntity() {
    Entity* entity = new Entity();
    std::unique_ptr<Entity> entityPtr{ entity };
    m_entities.emplace_back(std::move(entityPtr));
    return *entity;
}
