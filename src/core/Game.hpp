#pragma once

#include <SFML/Graphics.hpp>
#include "scenes/SceneManager.hpp"
#include "scenes/Gameplay.hpp"
#include "scenes/Settings.hpp"

#include "gameObjects/Player.hpp"
#include "gameObjects/Tile.hpp"

class Game {
public:
    Game(sf::ContextSettings& settings);
    void run();

private:
    sf::RenderWindow window;
    sf::Clock deltaClock;

    float deltaTime;

    void processEvents();
    void update(float fixedTimeStep);
    void render();
};
