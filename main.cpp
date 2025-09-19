#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

using coord = pair<int, int>;
int turnCount = 0;
bool switchTurn = true;

map<char, coord> ticMap = {
    {'1', {0, 0}},
    {'2', {0, 1}},
    {'3', {0, 2}},
    {'4', {1, 0}},
    {'5', {1, 1}},
    {'6', {1, 2}},
    {'7', {2, 0}},
    {'8', {2, 1}},
    {'9', {2, 2}},
};

char gameBox[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
};

int combos[8][3][2] = {
    {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}},
    {{2, 0}, {2, 1}, {2, 2}},
    {{0, 0}, {1, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}},
    {{0, 0}, {1, 1}, {2, 2}},
    {{0, 2}, {1, 1}, {2, 0}}};

void initGame()
{
    char v = '1';
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gameBox[i][j] = v++;
        }
    }
    turnCount = 0;
    switchTurn = true;
}

bool checkWinCondition(char &winner)
{
    for (auto &combo : combos)
    {
        char a = gameBox[combo[0][0]][combo[0][1]];
        char b = gameBox[combo[1][0]][combo[1][1]];
        char c = gameBox[combo[2][0]][combo[2][1]];
        if (a == b && b == c && (a == 'X' || a == 'O'))
        {
            winner = a;
            return true;
        }
    }
    return false;
}


void printGameBox()
{
    int column = sizeof(gameBox[0]) / sizeof(gameBox[0][0]);
    int rows = sizeof(gameBox) / sizeof(gameBox[0]);
    for (int i = 0; i < rows; i++)
    {
        string line;
        string line2;

        for (int j = 0; j < rows; j++)
        {
            if (j > 0)
                line += '|';
            line += ' ';
            line += gameBox[i][j];
            if (j > 0)
                line2 += '+';
            line2 += '-';
            line2 += '-';
        }

        cout << line << endl;

        if (i < rows - 1)
            cout << line2 << endl;
    }
}

bool cellCheck(char input)
{
    coord positionToInsert = ticMap[input];
    char cellToCheck = gameBox[positionToInsert.first][positionToInsert.second];
    return (cellToCheck != 'X' && cellToCheck != 'O');
}

bool checkInput(char input)
{
    return ticMap.find(input) != ticMap.end();
}

void startGame()
{
    printGameBox();
    if (switchTurn)
        cout << "Choose a position from the table for X:" << endl;
    else
        cout << "Choose a position from the table for O:" << endl;

    char positionSelected;
    cin >> positionSelected;

    if (!checkInput(positionSelected))
    {
        cout << "Insert a valid position" << endl;
        return;
    }

    if (!cellCheck(positionSelected))
    {
        cout << "Choose another cell" << endl;
        return;
    }

    coord pos = ticMap[positionSelected];
    gameBox[pos.first][pos.second] = switchTurn ? 'X' : 'O';
    switchTurn = !switchTurn;
    turnCount++;
}


int main()
{
    char playAgain;
    do
    {
        initGame();

        char winner = ' ';
        bool gameEnded = false;

        while (turnCount < 9)
        {
            startGame();
            if (checkWinCondition(winner))
            {
                printGameBox();
                cout << "Winner: " << winner << endl;
                gameEnded = true;
                break;
            }
        }

        if (!gameEnded && turnCount >= 9)
        {
            printGameBox();
            cout << "Draw" << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    return 0;
}
