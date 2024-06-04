#pragma once
class Player {
private:
    char* username;
    unsigned int bestScore;

public:
    Player(const char* username);
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player();
    const char* getUsername() const;
    int getBestScore() const;
    void setBestScore(unsigned int score, Player& player);
    void loadPlayerData();
    void savePlayerData(const Player& player);
};
