#ifndef LIVESMANAGER_H
#define LIVESMANAGER_H

class LivesManager {
private:
    int lives;

public:
    LivesManager(int initialLives);
    LivesManager(const LivesManager& other); // Copy constructor
    LivesManager(LivesManager&& other) noexcept; // Move constructor
    LivesManager& operator=(const LivesManager& other); // Copy assignment operator
    LivesManager& operator=(LivesManager&& other) noexcept; // Move assignment operator
    ~LivesManager(); // Destructor

    void decreaseLife();
    void resetLives(int initialLives);
    int getLives() const;
};

#endif // LIVESMANAGER_H
