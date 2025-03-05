#pragma once
#include <iostream>
#include <cmath>
#include <SFML/System.hpp>

struct Vector2 {
    float x = 0.0f, y = 0.0f;

    constexpr Vector2() noexcept = default;
    constexpr Vector2(float x, float y) noexcept : x(x), y(y) {}

    template <typename T>
    explicit constexpr Vector2(const sf::Vector2<T>& v) noexcept 
        : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)) {}

    [[nodiscard]] constexpr Vector2 operator+(const Vector2& other) const noexcept { return {x + other.x, y + other.y}; }
    [[nodiscard]] constexpr Vector2 operator-(const Vector2& other) const noexcept { return {x - other.x, y - other.y}; }
    [[nodiscard]] constexpr Vector2 operator*(float f) const noexcept { return {x * f, y * f}; }
    [[nodiscard]] constexpr Vector2 operator/(float f) const noexcept { return {x / f, y / f}; }
    [[nodiscard]] friend constexpr Vector2 operator*(float f, const Vector2& v) noexcept { return {v.x * f, v.y * f}; }
    Vector2& operator+=(const Vector2& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }

    [[nodiscard]] constexpr float distance(const Vector2& a, const Vector2& b) const noexcept {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    [[nodiscard]] constexpr float dot(const Vector2& other) const noexcept {
        return x * other.x + y * other.y;
    }

    [[nodiscard]] float magnitude() const noexcept {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] Vector2 normalized() const noexcept {
        float mag = magnitude();
        return (mag > 0.0f) ? Vector2(x / mag, y / mag) : Vector2{};
    }

    [[nodiscard]] sf::Vector2f toSFML() const noexcept {
        return sf::Vector2f(x, y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        return os << "Vector2(" << vec.x << ", " << vec.y << ")";
    }
};
