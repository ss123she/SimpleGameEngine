#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.hpp"

class SceneManager {
public:
    static SceneManager& getInstance();

    static void update(float dt);
    static void render(sf::RenderWindow& window);
    static void handleInput(const sf::Event& event);

    static void addScene(const std::string& name, std::shared_ptr<Scene> scene);
    
    static void setActiveScene(const std::string& name);

    static std::shared_ptr<Scene> getActiveScene();

private:
    static std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    static std::shared_ptr<Scene> activeScene;
};
