#pragma once
#include "Component.hpp"
#include <functional>

class ScriptComponent : public Component {
private:
    std::function<void(GameObject*, float)> updateFunc;
public:
    explicit ScriptComponent(std::function<void(GameObject*, float)>&& func) 
        : updateFunc(std::move(func)) {}

    void update(float deltaTime) override { updateFunc(owner, deltaTime); }
    void render(sf::RenderWindow& window) override {}
    void handleInput(const sf::Event& event) override {}

    std::string getType() const override { return "ScriptComponent"; }
};
