#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "gameObjects/GameObject.hpp"

class GameObjectFactory {
public:
    using CreateFunc = std::function<std::shared_ptr<GameObject>()>;

    static GameObjectFactory& getInstance() {
        static GameObjectFactory instance;
        return instance;
    }

    template <typename T>
    void registerType(const std::string& type) {
        static_assert(std::is_base_of<GameObject, T>::value, "T must be derived from GameObject");
        registry[type] = []() -> std::shared_ptr<GameObject> {
            return std::make_shared<T>();
        };
        std::cout << "Registered: " << type << std::endl;
    }

    std::shared_ptr<GameObject> createObjectByType(const std::string& type) {
        std::cout << "Looking for type: " << type << std::endl;
        
        if (registry.empty()) {
            std::cerr << "Error: registry is empty!" << std::endl;
            throw std::runtime_error("Registry is empty!");
        }
    
        std::cout << "Registry contents: " << std::endl;
        for (const auto& entry : registry) {
            std::cout << "Type: " << entry.first << std::endl;
        }
    
        auto it = registry.find(type);
        if (it != registry.end() && it->second) {
            std::cout << "Creating object..." << std::endl;
            try {
                auto obj = it->second();
                std::cout << "Object created successfully!" << std::endl;
                return obj;
            } catch (const std::exception& e) {
                std::cerr << "Exception while creating object: " << e.what() << std::endl;
                throw;
            }
        }
    
        std::cerr << "Error: Could not find type: " << type << std::endl;
        throw std::runtime_error("Unknown GameObject type: " + type);
    }

private:
   std::unordered_map<std::string, CreateFunc> registry;
};
