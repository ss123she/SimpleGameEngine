#include "RenderComponent.hpp"
#include <iostream>
#include <unordered_map>
#include "../../Vector2.hpp"
#include "../GameObject.hpp"

static std::unordered_map<std::string, sf::Texture> textureCache;

RenderComponent::RenderComponent(const std::string& path, bool isRender) : isRender(isRender) {
    if (!path.empty()) {
        if (textureCache.find(path) == textureCache.end()) {
            sf::Texture texture;
            if (texture.loadFromFile(path))
                textureCache[path] = std::move(texture);
            else
                std::cerr << "Error loading texture: " << path << std::endl;
        }
        
        if (textureCache.find(path) != textureCache.end()) {
            sprite.setTexture(textureCache[path]);
            texturePath = path;
            useTexture = true;
        } else
            useTexture = false;
    } else
        useTexture = false;
    
    if (!useTexture)
        shape.setFillColor(sf::Color::White);
}

void RenderComponent::render(sf::RenderWindow& window) {
    if (!owner || !isRender) return;
    
    auto transform = owner->getComponent<TransformComponent>();
    if (!transform) return;
    
    Vector2 pos = transform->getPosition();
    Vector2 size = transform->getSize();
    float rotation = transform->getRotation();
    
    if (useTexture) {
        sprite.setPosition(pos.x, pos.y);
        if (size.x > 0 && size.y > 0) {
            sf::Vector2u textureSize = textureCache[texturePath].getSize();
            sprite.setScale(size.x / static_cast<float>(textureSize.x), 
                            size.y / static_cast<float>(textureSize.y));
            sprite.setRotation(rotation);
        }
        window.draw(sprite);
    } else {
        shape.setPosition(pos.x, pos.y);
        shape.setSize({size.x, size.y});
        window.draw(shape);
    }
}

void RenderComponent::setRender(bool render) {
    isRender = render;
}

bool RenderComponent::getRender() const {
    return isRender;
}

std::string RenderComponent::getType() const {
    return "RenderComponent";
}

void RenderComponent::setTexture(const std::string& path) {
    if (textureCache.find(path) == textureCache.end()) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            textureCache[path] = std::move(texture);
        } else {
            std::cerr << "Error loading texture: " << path << std::endl;
            return;
        }
    }
    
    sprite.setTexture(textureCache[path]);
    texturePath = path;
    useTexture = true;
}

void RenderComponent::setFillColor(const sf::Color& color) {
    shape.setFillColor(color);
    useTexture = false;
}

const sf::Sprite& RenderComponent::getSprite() const {
    return sprite;
}

std::string RenderComponent::getTexturePath() const {
    return texturePath;
}
