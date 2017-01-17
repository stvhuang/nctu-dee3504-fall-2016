#include <iostream>
#include <fstream>
//#include <string>

using namespace std;

// Class cell stores color and fix or not
class cell
{
public:
    cell();
    ~cell();

    // 0: yellow, 1: blue, x: random
    bool set_color(char col);
    char get_color();
    bool is_fixed();

private:
    char color;
    bool fixed;
};

int main(int argc, char** argv)
{
    int width(0), height(0);
    char tmp('x');

    ifstream inFile(argv[1]);

    inFile >> width >> height;
    cout << "width: " << width << "\theight: " << height << endl;

    // Allocate memory for cell_table
    cell** cell_table = new cell* [height];
    for (int i(0); i < height; ++i)
    {
        cell_table[i] = new cell[width];
    }

    // construct cell_table
    for (int i(0); i < height; ++i)
    {
        for (int j(0); j < width; ++j)
        {
            inFile >> tmp;
            cell_table[i][width - j - 1].set_color(static_cast<char>(tmp));
        }
    }

    inFile.close();

    // Algorithm

    // Algorithm

    // Display cell_table
    cout << "Color, Fix" << endl;
    for (int i(0); i < height; ++i)
    {
        for (int j(0); j < width; ++j)
            cout << cell_table[i][j].get_color() << ", " << cell_table[i][j].is_fixed() << "\t";
        cout << endl;
    }
    cout << endl;

    // Delete memory allocated for cell_table
    for (int i(0); i < height; ++i)
    {
        delete [] cell_table[i];
    }
    delete [] cell_table;

    return 0;
}

cell::cell() : color('x'), fixed(false) {}

cell::~cell() {}

bool cell::set_color(char col)
{
    if (col == 'x' || col == '1' || col == '0')
    {
        if (fixed == false)
        {
            color = col;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

char cell::get_color()
{
    return color;
}

bool cell::is_fixed()
{
    return fixed;
}
