#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include "Player.h"

constexpr char FILE_NAME[] = "PlayersInfo.txt";
constexpr char TEMP_FILE_NAME[] = "TempFile.txt";

Player::Player(const char* uname) : bestScore(0) {
    username = new char[strlen(uname) + 1];
    std::strcpy(username, uname);
    loadPlayerData();
}

Player::Player(const Player& other) : bestScore(other.bestScore) {
    username = new char[strlen(other.username) + 1];
    std::strcpy(username, other.username);
}

Player& Player::operator=(const Player& other) {
    if (this == &other) {
        return *this;
    }

    delete[] username;

    username = new char[strlen(other.username) + 1];
    std::strcpy(username, other.username);
    bestScore = other.bestScore;

    return *this;
}

Player::~Player()
{
    delete[] username;
}

const char* Player::getUsername() const {
    return username;
}

int Player::getBestScore() const {
    return bestScore;
}

void Player::setBestScore(unsigned int score, Player& player) {
    if (score > bestScore) {
        player.bestScore = score;
        savePlayerData(player);
    }
}

void Player::loadPlayerData() {
    std::ifstream file(FILE_NAME);
    if (!file.is_open()) return;

    char fileUsername[50];
    int fileBestScore;
    while (file >> fileUsername >> fileBestScore) {
        if (std::strcmp(fileUsername, username) == 0) {
            bestScore = fileBestScore;
            break;
        }
    }
    file.close();
}

void Player::savePlayerData(const Player& player) {
    std::ifstream infile(FILE_NAME);
    std::ofstream tempFile(TEMP_FILE_NAME);
    if (!tempFile.is_open())
        return;
    if (!infile.is_open()) 
        return;

    char fileUsername[50];
    int fileBestScore;
    bool found = false;

    while (infile >> fileUsername >> fileBestScore) {
        if (std::strcmp(fileUsername, player.getUsername()) == 0) {
            tempFile << player.getUsername() << " " << player.getBestScore()<< "\n";
            found = true;
        }
        else {
            tempFile << fileUsername << " " << fileBestScore << "\n";
        }
    }

    if (!found) {
        tempFile << username << " " << bestScore << "\n";
    }

    infile.close();
    tempFile.close();
    std::remove(FILE_NAME);
    std::rename(TEMP_FILE_NAME, FILE_NAME);
}


