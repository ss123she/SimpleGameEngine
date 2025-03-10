#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <typeindex>
#include <vector>

#include "Components/Component.hpp"
#include "Components/TransformComponent.hpp"
#include "../Vector2.hpp"
#include "Utils.hpp"

class GameObject {
public:
    GameObject(Vector2 pos = {0, 0}, Vector2 size = {0, 0}) {
        addComponent<TransformComponent>(pos, size);
    }
    virtual ~GameObject() = default;

    void update(float dt);
    void render(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);

    virtual std::string getType() const = 0;
    std::vector<std::unique_ptr<Component>>& getComponents() {
        return components;
    }

    template <typename T, typename... Args>
    T* addComponent(Args&&... args) {
        size_t typeID = getComponentID<T>();
        if (typeID >= components.size()) {
            components.resize(typeID + 1);
        }

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->setOwner(this);
    
        components[typeID] = std::move(component);
        return static_cast<T*>(components[typeID].get());
    }

    void addTag(std::string tagName) {
        tags.push_back(tagName);
    }

    void deleteTag(std::string tagName) {
        tags.erase(std::find(tags.begin(), tags.end(), tagName), tags.end());
    }

    std::vector<std::string> getTags() const {
        return tags;
    }
    
    template <typename T>
    T* getComponent() {
        size_t typeID = getComponentID<T>();
        return (typeID < components.size()) ? static_cast<T*>(components[typeID].get()) : nullptr;
    }
    
    template <typename T>
    const T* getComponent() const {
        size_t typeID = getComponentID<T>();
        return (typeID < components.size()) ? static_cast<const T*>(components[typeID].get()) : nullptr;
    }
    
    template <typename T>
    void removeComponent() {
        size_t typeID = getComponentID<T>();
        if (typeID < components.size()) {
            components[typeID].reset();
        }
    }
    
    template <typename T>
    size_t getComponentID() {
        static const size_t id = nextID++;
        return id;
    }

private:
    std::vector<std::string> tags;
    std::vector<std::unique_ptr<Component>> components;
    static inline size_t nextID = 0;
};
