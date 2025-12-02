#include "Player.hpp"

Player::Player(const sf::Vector2f& startPos, float speed, float jumpForce)
    : _speed(speed), _jumpForce(jumpForce)
{
    _shape.setSize({30.f, 30.f});
    _shape.setFillColor(sf::Color::Red);
    _shape.setPosition(startPos);
    _velocity = {0.f, 0.f};
}

void Player::update(float dt, const sf::Image& levelMask) {
    sf::Vector2f pos = _shape.getPosition();
    
    // Space bar flips gravity / jump
    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    // Flip gravity only on key press (rising edge)
    if (spacePressed && !_spacePressedLastFrame) {
        _gravityFlipped = !_gravityFlipped;
        _velocity.y = _gravityFlipped ? -_jumpForce : _jumpForce;
    }

    _spacePressedLastFrame = spacePressed;

    // Gravity
    _velocity.y += _gravityFlipped ? -980.f * dt : 980.f * dt; // pixels per sec²

    // Predict next position
    sf::Vector2f nextPos = pos + _velocity * dt;

    // Collision check with white pixels
    if (!checkCollision(nextPos, levelMask)) {
        _shape.setPosition(nextPos);
    } else {
        // Stop vertical movement if collided
        _velocity.y = 0.f;
    }

    // Screen boundaries
    if (_shape.getPosition().y < 0) _shape.setPosition(pos.x, 0);
    if (_shape.getPosition().y + _shape.getSize().y > levelMask.getSize().y)
        _shape.setPosition(pos.x, levelMask.getSize().y - _shape.getSize().y);
}

void Player::render(sf::RenderWindow& window) {
    window.draw(_shape);
}

bool Player::checkCollision(const sf::Vector2f& pos, const sf::Image& levelMask) {
    // Get shape size as floats
    sf::Vector2f sizeF = _shape.getSize();

    // Convert to unsigned int for pixel coordinates
    unsigned int width = static_cast<unsigned int>(sizeF.x);
    unsigned int height = static_cast<unsigned int>(sizeF.y);

    auto isWhite = [&](unsigned int x, unsigned int y) {
        if (x >= levelMask.getSize().x || y >= levelMask.getSize().y) return false;
        sf::Color c = levelMask.getPixel(x, y);
        return c == sf::Color::White;
    };

    return isWhite(static_cast<unsigned int>(pos.x), static_cast<unsigned int>(pos.y)) ||
           isWhite(static_cast<unsigned int>(pos.x + width), static_cast<unsigned int>(pos.y)) ||
           isWhite(static_cast<unsigned int>(pos.x), static_cast<unsigned int>(pos.y + height)) ||
           isWhite(static_cast<unsigned int>(pos.x + width), static_cast<unsigned int>(pos.y + height));
}

