#pragma once

#include "GameObject.hpp"
#include "Components/Component.hpp"
#include "Components/RenderComponent.hpp"
#include "Components/ScriptComponent.hpp"

class Tile : public GameObject {
private:
    sf::RectangleShape shape;
    TransformComponent* transform;
    Vector2 initSize;
    bool upping;

public:
    Tile(const Vector2& position = {0, 0}, const Vector2& size = {50, 50});
    ~Tile();
    std::string getType() const override { return "Tile"; };

    void scriptUpdate(GameObject* obj, float deltaTime);

    void setFillColor(const sf::Color& color);
};
