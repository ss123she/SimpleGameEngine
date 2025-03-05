#pragma once
#include "Component.hpp"
#include <SFML/Window/Event.hpp>
#include <functional>

class InputComponent : public Component {
public:
    using InputHandler = std::function<void(const sf::Event&)>;
    
    explicit InputComponent(InputHandler handler) : inputHandler(handler) {}
    
    void handleInput(const sf::Event& event) override { if (inputHandler) inputHandler(event); }

    void update(float deltaTime) override {}

    void render(sf::RenderWindow& window) override {}

    std::string getType() const override { return "RenderComponent"; }

private:
    InputHandler inputHandler;
};
