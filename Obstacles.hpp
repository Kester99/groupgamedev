#pragma once
#include <SFML/Graphics.hpp>

class Obstacle {
public:
    Obstacle(float windowWidth, float windowHeight, bool top);

    void update(float dt);                 // Move obstacle left
    void render(sf::RenderWindow& window); // Draw obstacle
    sf::FloatRect getBounds() const;      // For collision detection

    bool isOffScreen() const;             // Check if it moved past the left edge

private:
    sf::RectangleShape _shape;
    float _speed;       // horizontal speed
    bool _top;
};
