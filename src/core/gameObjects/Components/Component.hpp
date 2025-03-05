#pragma once
#include <SFML/Graphics.hpp>

class GameObject;

class Component {
public:
    virtual ~Component() = default;

    void setOwner(GameObject* owner) { this->owner = owner; }
    GameObject* getOwner() { return owner; }

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void handleInput(const sf::Event& event) = 0;

    virtual std::string getType() const = 0;
    
protected:
    GameObject* owner = nullptr;
};
