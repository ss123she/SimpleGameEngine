#include "core/Game.hpp"

Game::Game(sf::ContextSettings& settings)
    : window(sf::VideoMode(800, 600), "LERP", sf::Style::Default, settings) {

    GameObjectFactory::getInstance().registerType<Player>("Player");
    GameObjectFactory::getInstance().registerType<Tile>("Tile");

    auto gameplayScene = std::make_shared<Gameplay>();
    SceneManager::addScene("Gameplay", gameplayScene);
    SceneManager::addScene("Settings", std::make_shared<Settings>());

    SceneManager::setActiveScene("Gameplay");
    gameplayScene->initialize();
}

void Game::run() {
    sf::Clock clock;
    float dt = 0.0f;

    while (window.isOpen()) {
        dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        SceneManager::handleInput(event);
    }
}

void Game::update(float dt) {
    SceneManager::update(dt);
    float fps = 1.0f / dt;
}

void Game::render() {
    window.clear();
    SceneManager::render(window);
    window.display();
}