#pragma once

#include <iostream>

class Utils {
public:
    static sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
        return start + t * (end - start);
    }

    // Easing functions
    static float easeIn(float t) {
        return t * t;
    }

    static float easeOut(float t) {
        return 1 - (1 - t) * (1 - t);
    }

    static float easeInOut(float t) {
        return t < 0.5f ? 2 * t * t : 1 - std::pow(-2 * t + 2, 2) / 2;
    }

    // logging
    enum class logLevel { INFO, WARNING, ERROR };
    static void log(const std::string& message, logLevel level = logLevel::INFO) {
        switch (level) {
            case logLevel::INFO:
                std::cout << "[INFO] " << message << std::endl;
                break;
            case logLevel::WARNING:
                std::cout << "[WARNING] " << message << std::endl;
                break;
            case logLevel::ERROR:
                std::cout << "[ERROR] " << message << std::endl;
                break;
        }
    }
};