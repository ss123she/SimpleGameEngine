#include "SceneManager.hpp"

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::update(float dt) {
    if (activeScene) {
        activeScene->update(dt);
    } else {
        std::cerr << "Warning: No active scene set in SceneManager::update()" << std::endl;
    }
}

void SceneManager::render(sf::RenderWindow& window) {
    if (activeScene) {
        activeScene->render(window);
    } else {
        std::cerr << "Warning: No active scene set in SceneManager::render()" << std::endl;
    }
}

void SceneManager::handleInput(const sf::Event& event) {
    if (activeScene) {
        activeScene->handleInput(event);
    } else {
        std::cerr << "Warning: No active scene set in SceneManager::handleInput()" << std::endl;
    }
}

void SceneManager::addScene(const std::string& name, std::shared_ptr<Scene> scene) {
    scenes[name] = scene;
}

void SceneManager::setActiveScene(const std::string& name) {
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        activeScene = it->second;
        std::cout << "Active scene set to: " << name << std::endl;
    } else {
        std::cerr << "Error: Scene '" << name << "' not found in SceneManager::setActiveScene()" << std::endl;
    }
}

std::shared_ptr<Scene> SceneManager::getActiveScene() {
    return activeScene;
}

std::unordered_map<std::string, std::shared_ptr<Scene>> SceneManager::scenes;
std::shared_ptr<Scene> SceneManager::activeScene = nullptr;
