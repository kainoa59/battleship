// Battleship 4
// Luke Patterson
// 03/10/22

#include <iostream>
#include <iomanip>
#include "newBoard.h"
#include "ship.h"

using namespace std;

const int rows = 10;
const int cols = 10;
const int MAXROWS = 10;
const int MAXCOLS = 10;
int HitCount = 0;
int MissCount = 0;
string board[rows][cols];
string playerBoard[rows][cols];
newBoard *playBoard = new newBoard();
newBoard *compBoard = new newBoard();
newBoard *originalBoard = new newBoard();
void newGuess();

void setShip(ship thisShip)
{
    bool flag;
    int col;
    int row;
    int orientation;

    do
    {
        flag = 0;
        col = rand() % 10;
        row = rand() % 10;
        orientation = rand() % 2;

        // Vertical Fit Test
        for (int e = 0; e < thisShip.getSize(); e++)
        {
            if (compBoard->getElement(row + e, col) != "[-]")
            {
                flag = 1;
            }
            if ((orientation == 0) && ((row + thisShip.getSize()) > 9))
            {
                flag = 1;
            }
        }

        // Horizontal Fit Test
        for (int e = 0; e < thisShip.getSize(); e++)
        {
            if (compBoard->getElement(row, col + e) != "[-]")
            {
                flag = 1;
            }
            if ((orientation == 1) && ((col + thisShip.getSize()) > 9))
            {
                flag = 1;
            }
        }

    } while (flag == 1);

    // Placing pieces on board according to orientation
    if (orientation == 0)
    {
        for (int q = 0; q < thisShip.getSize(); q++)
        {
            compBoard->setElement(row + q, col, "[" + thisShip.getName() + "]");
            originalBoard->setElement(row + q, col, "[" + thisShip.getName() + "]");
        }
    }

    if (orientation == 1)
    {
        for (int w = 0; w < thisShip.getSize(); w++)
        {
            compBoard->setElement(row, col + w, "[" + thisShip.getName() + "]");
            originalBoard->setElement(row, col + w, "[" + thisShip.getName() + "]");
        }
    }
}

int main()
{
    cout << ""
    "                                      # #  ( )\n"
    "                                  ___#_#___|_|_\n"
    "                              _  |____________|  _\n"
    "                       _=====| | |            | | |==== _\n"
    "                 =====| |.---------------------------. | |====\n"
    "   <--------------------'   .  .  .  .  .  .  .  .   '---------------/\n"
    "     \\                     WELCOME TO BATTLESHIP                    /\n"
    "      \\_____________________________________________SS_C++_________/\n"
    "  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
    "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n"
    "   wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n\n\n" << endl;

    cout << "Instructions: \n" << endl;
    cout << "-- To play, you must guess a spot on the board.\n\n"
    "-- All spots are respresented by a letter A-J for the columns and a number 1-10 for the rows (i.e. D7 is column D row 7).\n\n"
    "-- The game will ask for your guess and all you have to do is type the letter of your guess followed by the number\n"
    "(all capitals and no spaces).\n\n"
    "-- Repeated guesses will be counted against your score.\n\n"
    "-- There are 5 ships you need to uncover, and they have the sizes as follows: 2, 3, 3, 4, 5.\n\n"
    "-- They will be randomly placed on the board and can be vertical or horizontal, and they do not overlap.\n\n"
    "-- Once you miss 15 times, (represented by [O] and shown by the Miss Count score) the \n"
    "game ends and you lose. If you hit all ships (represented by [X] and shown by the Hit Count score) the\n"
    "game ends and you win!\n\n"
    "-- To leave the game early simply type -1 at any time. Have fun!\n\n\n" << endl;

    srand(time(0));

    // Constructing board
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            compBoard->setElement(r, c, "[-]");
            playBoard->setElement(r, c, "[-]");
            originalBoard->setElement(r, c, "[-]");
        }
    };

    playBoard->printMatrix();

    // Filling array with ship elements
    ship Arr[5] = {ship("F", 2), ship("S", 3), ship("D", 3), ship("B", 4), ship("A", 5)};

    // Calling the setShip function to place pieces on board
    for (int i = 0; i < 5; i++)
    {
        setShip(Arr[i]);
    }
    newGuess();
    return 0;
}

void newGuess()
{
    string userGuess;
    char userRow;
    char userCol;
    int intUserCol;
    int intUserRow;
    int length = 3;

    // Ask user for their guess and take it in as a string
    cout << "\n\nEnter your guess, or -1 to end the game:" << endl;
    getline(cin, userGuess);

    // End game function
    if (userGuess == "-1")
    {
        cout << "Game Over!" << endl;
        return;
    }

    // Parse string into array
    char charArray[length + 1];
    strcpy(charArray, userGuess.c_str());

    // Save columns and rows into variables
    userCol = charArray[0];
    intUserRow = (charArray[1] - '0') - 1;
    if (charArray[2])
    {
        intUserRow = 9;
    }

    // Convert character to number
    for (int i = 0; i < 10; i++)
    {
        if (int(userCol) == 65 + i)
        {
            intUserCol = 0 + i;
        }
    }

    // Check for a miss otherwise hit
    if (compBoard->getElement(intUserRow, intUserCol) == "[-]")
    {
        playBoard->setElement(intUserRow, intUserCol, "[O]");
        compBoard->setElement(intUserRow, intUserCol, "[O]");

        MissCount = MissCount + 1;
    }
    else if (compBoard->getElement(intUserRow, intUserCol) == "[O]") 
    {
        MissCount = MissCount + 1;
    } else 
    {
        playBoard->setElement(intUserRow, intUserCol, "[X]");
        compBoard->setElement(intUserRow, intUserCol, "[X]");

        HitCount = HitCount + 1;
    }

    cout << "\nMiss Count: " << MissCount << "/15" << endl;
    cout << "Hit Count: " << HitCount << "/17" << endl;

    playBoard->printMatrix();

    if (HitCount < 17 && MissCount < 15)
    {
        newGuess();
    }
    else if (HitCount == 17)
    {
        cout << "\n\nYou Win!!\n\n";
        cout << "The correct board was: \n\n";
        originalBoard->printMatrix();

    }
    else if (MissCount == 15)
    {
        cout << "\n\nYou Lose!!\n\n";
        cout << "The correct board was: \n\n";
        originalBoard->printMatrix();
    }
    return;
}