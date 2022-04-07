#include <iostream>
#include <iomanip>
using namespace std;

class newBoard
{
private:
    string doubleArray[10][10];
    static const int rows = 10;
    static const int cols = 10;

public:
    newBoard(){
        string doubleArray[rows][cols];
    }; 

    //Getter Functions
    void printMatrix()
    {
        cout << "   A  B  C  D  E  F  G  H  I  J" << endl;
        for (int i = 0; i < rows; i++)
        {
            cout << setw(2) << i + 1;
            for (int j = 0; j < cols; j++)
            {
                cout << doubleArray[i][j];
            }
            cout << endl;
        }
    };

    //Setter Functions
    void setElement(int row, int col, string value)
    {
        doubleArray[row][col] = value;
    };  
                                                
    string getElement(int row, int col) {
        return doubleArray[row][col];
    };

};