#include "Player.hpp"
#include "../scenes/SceneManager.hpp"
#include "../GameObjectFactory.hpp"
#include "../FileManager.hpp"

Player::Player() : GameObject({0, 0}, {0, 0}) {
    std::filesystem::path cwd = std::filesystem::current_path();
    
    addComponent<RenderComponent>("", true);
    addComponent<ScriptComponent>(std::bind(&Player::scriptUpdate, this, std::placeholders::_1, std::placeholders::_2));

    std::function<void(const sf::Event&)> inputHandler = [this](const sf::Event& event) {
        processInput(event);
    };
    addComponent<InputComponent>(inputHandler);

    transform = getComponent<TransformComponent>();

    scene = SceneManager::getActiveScene() ? : nullptr;

    camera = scene ? scene->getCamera() : nullptr;
    camera->setSize(800, 600);
    camera->setCenter(transform->getPosition().toSFML());
}

void Player::processInput(const sf::Event& event) {
    velocity = {0.0f, 0.0f};
    scene = SceneManager::getActiveScene() ? : nullptr;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y = -200.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y = 200.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x = -200.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x = 200.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        std::shared_ptr<GameObject> obj = GameObjectFactory::getInstance().createObjectByType("Player");
        obj->getComponent<TransformComponent>()->setPosition(transform->getPosition());
        scene->addObject(obj);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        std::shared_ptr<GameObject> obj = GameObjectFactory::getInstance().createObjectByType("Tile");
        obj->getComponent<TransformComponent>()->setPosition(transform->getPosition());
        if (scene) scene->addObject(obj);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        FileManager::SaveMap(scene->getGameObjects());
        scene->setGameObjects(FileManager::LoadMap());
    }
}

void Player::scriptUpdate(GameObject* obj, float deltaTime) {
    std::cout << "Num of objects: " << scene->getGameObjects().size() << std::endl << "FPS: " << 1.0f / deltaTime << std::endl;
    transform->setPosition(transform->getPosition() + velocity * deltaTime);

    if (scene && camera) {
        sf::Vector2f targetPosition = transform->getPosition().toSFML();
        float smoothFactor = 5.0f * deltaTime;
        sf::Vector2f newCenter = Utils::lerp(camera->getCenter(), targetPosition, smoothFactor);
        camera->setCenter(newCenter);
    }
}