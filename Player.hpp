// Player.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(const sf::Vector2f& startPos, float speed, float jumpForce);

    void update(float dt, const sf::Image& levelMask);
    void render(sf::RenderWindow& window);

    // Add this getter
    const sf::RectangleShape& getShape() const { return _shape; }

private:
    sf::RectangleShape _shape;
    sf::Vector2f _velocity;
    float _speed;
    float _jumpForce;
    bool _gravityFlipped = false;
    bool _spacePressedLastFrame = false; 
    bool checkCollision(const sf::Vector2f& pos, const sf::Image& levelMask);
};

