#pragma once

#include "core/gameObjects/GameObject.hpp"
#include "core/gameObjects/Components/RenderComponent.hpp"
#include "core/gameObjects/Components/ScriptComponent.hpp"
#include "core/gameObjects/Components/InputComponent.hpp"
#include "core/Vector2.hpp"

class Scene;

class Player : public GameObject {
private:
    std::shared_ptr<Scene> scene = nullptr;
    TransformComponent* transform;
    Vector2 velocity = Vector2(0, 0);
    sf::View* camera;
public:
    Player();

    // Getters
    const Vector2& getVelocity() const { return velocity; }
    std::string getType() const override { return "Player"; }

    // Setters
    void setVelocity(const Vector2& newVelocity) { velocity = newVelocity; }

    void processInput(const sf::Event& event);
    void scriptUpdate(GameObject* obj, float deltaTime);
};