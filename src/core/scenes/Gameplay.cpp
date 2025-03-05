#include "Gameplay.hpp"
#include "../GameObjectFactory.hpp"
#include "../GameObject.hpp"

Gameplay::Gameplay() {}

void Gameplay::initialize() {
    std::shared_ptr<GameObject> player = GameObjectFactory::getInstance().createObjectByType("Player");
    addObject(player);

    for (int x=0; x < 50; x++) {
        for (int y=0; y < 50; y++) {
            std::shared_ptr<GameObject> tile = GameObjectFactory::getInstance().createObjectByType("Tile");
            tile->getComponent<TransformComponent>()->setPosition({static_cast<float>(x * 100), static_cast<float>(y * 100)});
            addObject(tile);
        }
    }
}