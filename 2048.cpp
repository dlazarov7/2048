#include <iostream>

int board[4][4];
int dirLine[] = { 1,0, - 1,0 };
int dirColumn[] = { 1,0,-1,0 };

void newGame() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            board[i][j] = 0;
}

void printUI() {
    for (int i = 0; i < 4; ++i) {

        for (int j = 0; j < 4; ++j)
            if (board[i][j] == 0)
                std::cout << " ";
            else
                std::cout << board[i][j];
    std::cout << "\n";
    }
    std::cout << "n: new game, w: up, s: down, d: right, a: left, q: quit\n";
}

int main()
{
    char commandToDir[128]; //0-128 ascii chars
    commandToDir['s'] = 0;
    commandToDir['d'] = 1;
    commandToDir['w'] = 2;
    commandToDir['a'] = 3;
    newGame();
    while (true)
    {
        printUI();
        char command;
        std::cin >> command;

        if (command == 'n') {
            newGame(); 
        }
        else if (command == 'q') {
            break;
        }
        else {
            int currentDirection = commandToDir[command];
            std::cout << currentDirection;
            //applyMove(currentDirection); to do
        }
    }
    return 0;
}

