#include "livesManager.h"

LivesManager::LivesManager(int initialLives) : lives(initialLives) {}

LivesManager::LivesManager(const LivesManager& other) : lives(other.lives) {}

LivesManager::LivesManager(LivesManager&& other) noexcept : lives(other.lives) {
    other.lives = 0;
}

LivesManager& LivesManager::operator=(const LivesManager& other) {
    if (this != &other) {
        lives = other.lives;
    }
    return *this;
}

LivesManager& LivesManager::operator=(LivesManager&& other) noexcept {
    if (this != &other) {
        lives = other.lives;
        other.lives = 0;
    }
    return *this;
}

LivesManager::~LivesManager() {}

void LivesManager::decreaseLife() {
    if (lives > 0) {
        lives--;
    }
}

void LivesManager::resetLives(int initialLives) {
    lives = initialLives;
}

int LivesManager::getLives() const {
    return lives;
}