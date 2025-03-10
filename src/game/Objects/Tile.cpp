#include "Tile.hpp"

#include <filesystem>

Tile::Tile(const Vector2& position, const Vector2& size) : GameObject(position, size) {
    initSize = size;
    transform = getComponent<TransformComponent>();
    transform->setPosition(position);
    transform->setSize(size);

    shape.setPosition(position.x, position.y);
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setFillColor(sf::Color::White);

    addComponent<RenderComponent>("assets/textures/Tile.jpg");
    addComponent<ScriptComponent>(std::bind(&Tile::scriptUpdate, this, std::placeholders::_1, std::placeholders::_2));
}
Tile::~Tile() {
    removeComponent<RenderComponent>();
    removeComponent<ScriptComponent>();
}

void Tile::scriptUpdate(GameObject* obj, float deltaTime) {
    float targetHeight = initSize.y + 100;
    float currentHeight = transform->getSize().y;

    transform->setRotation(transform->getRotation() + 50 * deltaTime);

    if (upping) {
        if (currentHeight < targetHeight) {
            transform->setSize(transform->getSize() + Vector2(25 * deltaTime, 25 * deltaTime));
        } else {
            upping = false;
        }
    } else {
        if (currentHeight > initSize.y) {
            transform->setSize(transform->getSize() + Vector2(-25 * deltaTime, -25* deltaTime));
        } else {
            upping = true;
        }
    }
}

void Tile::setFillColor(const sf::Color& color) {
    shape.setFillColor(color);
}
