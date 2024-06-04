#pragma warning(disable: 4244)
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "Player.h"

int board[4][4];
int dirLine[] = { 1, 0, -1, 0 };
int dirColumn[] = { 0, 1, 0, -1 };
int currentScore = 0;

std::pair<int, int> generateUnoccupiedPosition() {
    int occupied = 1, line, column;
    while (occupied) {
        line = rand() % 4;
        column = rand() % 4;
        if (board[line][column] == 0)
            occupied = 0;
    }
    return std::make_pair(line, column);
}

void addPiece() {
    std::pair<int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = 2;
}

void newGame() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            board[i][j] = 0;
    addPiece();
    currentScore = 0;
}

void printUI(const Player& player) {
    system("cls");
    std::cout << "Player: " << player.getUsername() << "\n";
    std::cout << "Score: " << currentScore << "\n";
    std::cout << "Best Score: " << player.getBestScore() << "\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0)
                std::cout << std::setw(4) << ".";
            else
                std::cout << std::setw(4) << board[i][j];
        std::cout << "\n";
    }
    std::cout << "n: new game, w: up, s: down, d: right, a: left, q: quit\n";
}

bool canDoMove(int line, int column, int nextLine, int nextColumn) {
    if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4
        || (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
        return false;
    return true;
}

void applyMove(int direction) {
    int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;
    if (direction == 0) {
        startLine = 3;
        lineStep = -1;
    }
    if (direction == 1) {
        startColumn = 3;
        columnStep = -1;
    }
    int movePossible = 0, canAddPiece = 0;
    do {
        movePossible = 0;

        for (int i = startLine; i >= 0 && i < 4; i += lineStep)
            for (int j = startColumn; j >= 0 && j < 4; j += columnStep) {
                int nextI = i + dirLine[direction], nextJ = j + dirColumn[direction];
                if (board[i][j] != 0 && canDoMove(i, j, nextI, nextJ)) {
                    if (board[nextI][nextJ] == board[i][j]) {
                        board[nextI][nextJ] += board[i][j];
                        currentScore += board[nextI][nextJ];
                    }
                    else {
                        board[nextI][nextJ] = board[i][j];
                    }
                    board[i][j] = 0;
                    movePossible = 1;
                    canAddPiece = 1;
                }
            }
    } while (movePossible);

    if (canAddPiece)
        addPiece();
}

int main() {
    srand(time(0));
    char commandToDir[128]; //0-128 ascii chars
    commandToDir['s'] = 0;
    commandToDir['d'] = 1;
    commandToDir['w'] = 2;
    commandToDir['a'] = 3;

    char username[50];
    std::cout << "Enter your username: ";
    std::cin >> username;
    Player player(username);

    player.savePlayerData(player);
    newGame();
    while (true) {
        printUI(player);
        char command;
        std::cin >> command;

        if (command == 'n') {
            player.setBestScore(currentScore, player);
            newGame();
        }
        else if (command == 'q') {
            player.setBestScore(currentScore, player);
            break;
        }
        else {
            int currentDirection = commandToDir[command];
            applyMove(currentDirection);
        }
    }
    return 0;
}
