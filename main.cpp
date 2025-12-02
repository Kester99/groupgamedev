#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Obstacles.hpp"
#include <vector>
#include <algorithm>

int main() {
    std::vector<Obstacle> obstacles;
    float obstacleSpawnTimer = 0.f;
	bool gameOver = true;
    sf::RenderWindow window(sf::VideoMode(800.f, 600.f), "Gravity Guy Minimal");
    window.setFramerateLimit(60);

    // Simple level mask (white boundaries)
    sf::Image levelMask;
    levelMask.create(800, 600, sf::Color::Black);
    // Draw white floor and ceiling
    for (unsigned x = 0; x < 800; ++x) {
        levelMask.setPixel(x, 0, sf::Color::White);      // ceiling
        levelMask.setPixel(x, 599, sf::Color::White);    // floor
    }

    Player player({50.f, 300.f}, 0.f, 400.f); // speed=0, stationary player

    sf::Clock clock;
    while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    float dt = clock.restart().asSeconds();

    if (!gameOver) {
        // Optionally, display game over text or freeze updates
    } else {
        // Game running: update player, obstacles, check collisions
        obstacleSpawnTimer += dt;
        if (obstacleSpawnTimer > 1.5f) {
            bool spawnTop = rand() % 2 == 0;
            obstacles.emplace_back(800.f, 600.f, spawnTop);
            obstacleSpawnTimer = 0.f;
        }

        for (auto& obs : obstacles)
            obs.update(dt);

        obstacles.erase(
            std::remove_if(obstacles.begin(), obstacles.end(),
                           [](const Obstacle& o){ return o.isOffScreen(); }),
            obstacles.end()
        );

        for (auto& obs : obstacles) {
            if (player.getShape().getGlobalBounds().intersects(obs.getBounds())) {
                gameOver = false;
                break;
            }
        }

        player.update(dt, levelMask);
    }

    // Render everything
    window.clear(sf::Color::Black);

    for (auto& obs : obstacles)
        obs.render(window);

    player.render(window);

    // Optionally display "Game Over" text
    window.display();
}}