#include "GameObject.hpp"

void GameObject::update(float dt)
{
    for (auto &component : components)
        component->update(dt);
}

void GameObject::render(sf::RenderWindow &window)
{
    for (auto &component : components)
        component->render(window);
}

void GameObject::handleInput(const sf::Event &event)
{
    for (auto &component : components)
        component->handleInput(event);
}
