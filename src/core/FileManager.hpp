#pragma once

#include "GameObjectFactory.hpp"
#include "Utils.hpp"
#include "gameObjects/Components/RenderComponent.hpp"
#include "gameObjects/Components/TransformComponent.hpp"
#include <fstream>
#include <filesystem>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <zlib/zlib.h>

class FileManager {
public:
    // Saves a vector of GameObjects to a file.
    inline static void SaveMap(const std::vector<std::shared_ptr<GameObject>>& objects, const std::string& fileName = "map.dat") {
        std::filesystem::path filePath = mapsDirectory / fileName;
        std::ofstream file(filePath, std::ios::binary);

        if (file.is_open()) {
            std::stringstream buffer;
            size_t objectCount = objects.size();
            buffer.write(reinterpret_cast<const char*>(&objectCount), sizeof(objectCount));

            for (const auto& obj : objects) {
                std::string type = obj->getType();
                size_t typeLength = type.size();
                buffer.write(reinterpret_cast<const char*>(&typeLength), sizeof(typeLength));
                buffer.write(type.c_str(), typeLength);

                auto transform = obj->getComponent<TransformComponent>();
                Vector2 position = transform->getPosition();
                buffer.write(reinterpret_cast<const char*>(&position), sizeof(position));
                Vector2 size = transform->getSize();
                buffer.write(reinterpret_cast<const char*>(&size), sizeof(size));

                auto renderComponent = obj->getComponent<RenderComponent>();
                std::string texturePath = renderComponent ? renderComponent->getTexturePath() : "";
                size_t texturePathLength = texturePath.size();
                buffer.write(reinterpret_cast<const char*>(&texturePathLength), sizeof(texturePathLength));
                buffer.write(texturePath.c_str(), texturePathLength);
            }

            std::string compressedData = CompressData(buffer.str());
            file.write(compressedData.c_str(), compressedData.size());
        }
    }

    // Loads a vector of GameObjects from a file.
    inline static std::vector<std::shared_ptr<GameObject>> LoadMap(const std::string& fileName = "map.dat") {
        std::vector<std::shared_ptr<GameObject>> objects;
        std::filesystem::path filePath = mapsDirectory / fileName;
        std::ifstream file(filePath, std::ios::binary);

        if (file.is_open()) {
            std::string compressedData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            std::string decompressedData = DecompressData(compressedData);
            std::stringstream buffer(decompressedData);

            size_t objectCount;
            buffer.read(reinterpret_cast<char*>(&objectCount), sizeof(objectCount));

            for (size_t i = 0; i < objectCount; ++i) {
                size_t typeLength;
                buffer.read(reinterpret_cast<char*>(&typeLength), sizeof(typeLength));
                std::string type(typeLength, '\0');
                buffer.read(&type[0], typeLength);

                auto obj = GameObjectFactory::getInstance().createObjectByType(type);
                if (obj) {
                    Vector2 position;
                    buffer.read(reinterpret_cast<char*>(&position), sizeof(position));
                    obj->getComponent<TransformComponent>()->setPosition(position);

                    Vector2 size;
                    buffer.read(reinterpret_cast<char*>(&size), sizeof(size));
                    obj->getComponent<TransformComponent>()->setSize(size);

                    size_t texturePathLength;
                    buffer.read(reinterpret_cast<char*>(&texturePathLength), sizeof(texturePathLength));
                    std::string texturePath(texturePathLength, '\0');
                    buffer.read(&texturePath[0], texturePathLength);

                    if (!texturePath.empty()) {
                        auto renderComponent = obj->getComponent<RenderComponent>();
                        if (renderComponent) {
                            renderComponent->setTexture(texturePath);
                        }
                    }

                    objects.push_back(obj);
                }
            }
        }
        return objects;
    }

private:
    // Compresses data using zlib.
    static std::string CompressData(const std::string& data) {
        uLongf compressedSize = compressBound(data.size());
        std::vector<char> compressedData(compressedSize);

        if (compress(reinterpret_cast<Bytef*>(compressedData.data()), &compressedSize,
                     reinterpret_cast<const Bytef*>(data.data()), data.size()) != Z_OK) {
            throw std::runtime_error("Compression failed");
        }

        return std::string(compressedData.begin(), compressedData.begin() + compressedSize);
    }

    // Decompresses data using zlib.
    static std::string DecompressData(const std::string& compressedData) {
        uLongf decompressedSize = compressBound(compressedData.size()) * 10; // Start with a larger buffer
        std::vector<char> decompressedData(decompressedSize);

        int result = uncompress(reinterpret_cast<Bytef*>(decompressedData.data()), &decompressedSize,
                                reinterpret_cast<const Bytef*>(compressedData.data()), compressedData.size());

        while (result == Z_BUF_ERROR) {
            decompressedSize *= 2;
            decompressedData.resize(decompressedSize);

            result = uncompress(reinterpret_cast<Bytef*>(decompressedData.data()), &decompressedSize,
                                reinterpret_cast<const Bytef*>(compressedData.data()), compressedData.size());
        }

        if (result != Z_OK) {
            throw std::runtime_error("Decompression failed with error code " + std::to_string(result));
        }

        return std::string(decompressedData.begin(), decompressedData.begin() + decompressedSize);
    }

    // Directory where map files are stored.
    static inline std::filesystem::path mapsDirectory = []() {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::filesystem::path mapsDir = cwd / "maps";
        if (!std::filesystem::exists(mapsDir)) {
            std::filesystem::create_directory(mapsDir);
        }
        return mapsDir;
    }();
};