#pragma once
class Player {
private:
    char* username; // Assuming the maximum length of a username is 50 characters
    int bestScore;

public:
    Player(const char* username);
    ~Player();
    const char* getUsername() const;
    int getBestScore() const;
    void setBestScore(int score, Player& player);
    void loadPlayerData();
    void savePlayerData(const Player& player);
};
