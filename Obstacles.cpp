#include "Obstacles.hpp"
#include <cstdlib> // for rand()
#include <ctime>

static bool firstObstacle = true; // ensure srand runs only once

Obstacle::Obstacle(float windowWidth, float windowHeight, bool top)
    : _top(top), _speed(200.f) // speed in pixels/sec
{
    if (firstObstacle) {
        std::srand(static_cast<unsigned>(std::time(nullptr))); // seed random once
        firstObstacle = false;
    }

    // Random size
    float width = 50.f + rand() % 50;    // 50-100 px
    float height = 50.f + rand() % 200;  // 50-250 px

    _shape.setSize({ width, height });
    _shape.setFillColor(sf::Color::White); // Obstacles are white

    // Randomly attach to floor or ceiling based on top flag
    float xPos = windowWidth; // spawn off-screen to the right
    float yPos = _top ? 0.f : windowHeight - height;

    _shape.setPosition(xPos, yPos);
}

void Obstacle::update(float dt) {
    _shape.move(-_speed * dt, 0.f); // move left
}

void Obstacle::render(sf::RenderWindow& window) {
    window.draw(_shape);
}

sf::FloatRect Obstacle::getBounds() const {
    return _shape.getGlobalBounds();
}

bool Obstacle::isOffScreen() const {
    return _shape.getPosition().x + _shape.getSize().x < 0 ;
}
