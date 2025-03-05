#pragma once
#include "Component.hpp"
#include "../../Vector2.hpp"

class TransformComponent : public Component {
private:
    Vector2 position;
    Vector2 size;
    float rotation;
public:
    TransformComponent(Vector2 pos, Vector2 size, float rotation = 0.0f) : position(pos), size(size), rotation(rotation) {}

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) override {}
    void handleInput(const sf::Event& event) override {}

    [[nodiscard]] Vector2 getPosition() const { return position; }
    [[nodiscard]] Vector2 getSize() const { return size; }
    [[nodiscard]] float getRotation() const { return rotation; }

    std::string getType() const override { return "TransformComponent"; }

    void setPosition(const Vector2& newPosition) { position = newPosition; }
    void setSize(const Vector2& newSize) { size = newSize; }
    void setRotation(float newRotation) { rotation = newRotation; }

    bool contains(float x, float y) const {
        return (x >= position.x && x <= position.x + size.x) &&
               (y >= position.y && y <= position.y + size.y);
    }
};