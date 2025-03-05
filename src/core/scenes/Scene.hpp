#pragma once

#include <SFML/Graphics.hpp>
#include "../FileManager.hpp"
#include "../gameObjects/GameObject.hpp"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void handleInput(const sf::Event& event) {
        for (auto& obj : m_gameObjects)
            obj->handleInput(event);
    }

    virtual void update(float deltaTime) {
        for (auto& obj : m_gameObjects)
            obj->update(deltaTime);
    }

    virtual void render(sf::RenderWindow& window) {
        window.setView(camera);
        for (auto& obj : m_gameObjects)
            obj->render(window);
    }

    void addObject(std::shared_ptr<GameObject> obj) {
        m_gameObjects.push_back(std::move(obj));
    }

    void saveScene() {
        FileManager::SaveMap(m_gameObjects);
    }

    void loadScene() {
        m_gameObjects = FileManager::LoadMap();
    }
    
    sf::View* getCamera() {
        return &camera;
    }

    std::vector<std::shared_ptr<GameObject>> getGameObjects() const {
        return m_gameObjects;
    }

    void setGameObjects(std::vector<std::shared_ptr<GameObject>> gameObjects) {
        m_gameObjects = std::move(gameObjects);
    }

protected:
    std::vector<std::shared_ptr<GameObject>> m_gameObjects;
    sf::View camera;
    std::vector<GameObject*> getRawPointers() const {
        std::vector<GameObject*> rawPointers;
        rawPointers.reserve(m_gameObjects.size());
        for (const auto& obj : m_gameObjects) {
            rawPointers.push_back(obj.get());
        }
        return rawPointers;
    }
};
