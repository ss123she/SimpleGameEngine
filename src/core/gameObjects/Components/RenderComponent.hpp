#pragma once
#include "Component.hpp"

#include <SFML/Graphics.hpp>

class RenderComponent : public Component {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape shape;
    std::string texturePath;
    bool useTexture = false;
    bool isRender = false;
    
public:
    RenderComponent(const std::string& path = "", bool isRender = true);
    void update(float dt) override {}
    void render(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event) override {}
    void setRender(bool render);
    bool getRender() const;
    std::string getType() const override;
    
    void setTexture(const std::string& path);
    void setFillColor(const sf::Color& color);
    const sf::Sprite& getSprite() const;
    std::string getTexturePath() const;
};