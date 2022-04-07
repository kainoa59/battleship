#include <iostream>
using namespace std;

class ship
{
private:
    string name;
    int size;

public:
    // Ship constructor
    ship(string Name, int Size)
    {
        name = Name;
        size = Size;
    }
    string getName()
    {
        return name;
    }
    int getSize()
    {
        return size;
    }
};