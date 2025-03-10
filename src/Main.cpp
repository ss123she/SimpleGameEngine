#include <iostream>
#include <SFML/Graphics.hpp>

#include "core/Game.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    Game game(settings);
    game.run();

    return 0;
}