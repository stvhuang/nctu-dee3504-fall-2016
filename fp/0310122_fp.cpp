#include <iostream>
#include <fstream>
//#include <string>

using namespace std;

template <class T>
void printTable(T** table, int height, int width)
{
    cout << endl;
    for (int i(0); i < height; ++i)
    {
        for (int j(0); j < width; ++j)
        {
            cout.width(2);
            cout << table[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return;
}

int indexToCcc(int i, int j, int height, int width)
{
    if (i == 0 || j == width - 1)
    {
        return 0;
    }
    else
    {
        int idx(0);
        idx = (i - 1) * (width - 1) + j + 1;
        return idx;
    }
}

int leastUnfixed(bool** table, int height, int width)
{
    for (int i(0); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if (table[j][i] == true)
            {
                continue;
            }
            else
            {
                //cout << "Height: " << j << "\tWidth: " << i << endl;
                return j * width + i;
            }
        }
    }
    return width * height - 1;
}

bool checkIfDone(bool** fixed_table, int height, int width)
{
    for (int i(1); i < height; ++i)
    {
        for (int j(0); j < width - 1; ++i)
        {
            if (fixed_table[i][j] == false)
            {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char** argv)
{
    int width(0), height(0);
    char tmp_char(static_cast<char>(0));
    int tmp_int(0);

    ifstream inFile(argv[1]);

    inFile >> width >> height;
    //cout << "width: " << width << "\nheight: " << height << endl;

    char** target_table = new char* [height];
    char** answer_table = new char* [height];
    bool** fixed_table = new bool* [height];
    for (int i(0); i < height; ++i)
    {
        target_table[i] = new char[width];
        answer_table[i] = new char[width];
        fixed_table[i] = new bool[width];
    }

    for (int i(0); i < height; ++i)
    {
        for (int j(0); j < width; ++j)
        {
            inFile >> tmp_char;
            target_table[i][width - j - 1] = tmp_char;
            answer_table[i][j] = '?';
            fixed_table[i][j] = false;
        }
    }

    inFile.close();

    // Algorithm
    //cout << "\nFixed: (Answer)" << endl;
    //printTable(fixed_table, height, width);
    tmp_int = leastUnfixed(fixed_table, height, width); // the target
    char target_color = target_table[tmp_int / width][tmp_int % width];
    //cout << tmp_int << " " << target_color << endl;
    int i(0), j(0); // i for height, j for width

    // Start to paint color
    while(i < height && j < width) // painting
    {
        if (j == width - 1 && i == height - 1) // at the down-right point
        {
            //cout << "break";
            break;
        }

        if (j == width - 1 || i == 0) // no need to care about color
        {
            ++i;
            continue;
        }
        else
        {
            if (fixed_table[i][j] == true) // color cannot be changed
            {
                ++j;
                --i;
            }
            else // color can be chaged
            {
                answer_table[i][j] = target_color;
                cout << indexToCcc(i, j, height, width) << endl;
                ++i;
                if (i == height && j < width - 1)
                {
                    --i;
                    ++j;
                }
            }
        }
    }

    for (int i(0); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if(answer_table[j][i] == target_table[j][i]) // same color
            {
                fixed_table[j][i] = true;
            }
            else if (j == height - 1) // wrong color
            {
                i = width;
                break;
            }
            else
            {
                break;
            }
        }
    }

    tmp_int = leastUnfixed(fixed_table, height, width); // the target
    target_color = target_table[tmp_int / width][tmp_int % width];
    //cout << tmp_int << " " << target_color << endl;

    // Start to paint color
    i = 0; j = 0;
    while(i < height && j < width) // painting
    {
        if (j == width - 1 && i == height - 1) // at the down-right point
        {
            //cout << "break";
            break;
        }

        if (j == width - 1 || i == 0) // no need to care about color
        {
            ++i;
            continue;
        }
        else
        {
            if (fixed_table[i][j] == true) // color cannot be changed
            {
                ++j;
                --i;
            }
            else // color can be chaged
            {
                answer_table[i][j] = target_color;
                ++i;
                if (i == height && j < width - 1)
                {
                    --i;
                    ++j;
                }
            }
        }
    }

    for (int i(0); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if(answer_table[j][i] == target_table[j][i]) // same color
            {
                fixed_table[j][i] = true;
            }
            else if (j == height - 1) // wrong color
            {
                i = width;
                break;
            }
            else
            {
                break;
            }
        }
    }

    tmp_int = leastUnfixed(fixed_table, height, width); // the target
    target_color = target_table[tmp_int / width][tmp_int % width];
    //cout << tmp_int << "asdfasdf " << target_color << endl;

    i = 0; j = 0;
    while(i < height && j < width) // painting
    {
        if (j == width - 1 && i == height - 1) // at the down-right point
        {
            //cout << "break";
            break;
        }

        if (j == width - 1 || i == 0) // no need to care about color
        {
            ++i;
            continue;
        }
        else
        {
            if (fixed_table[i][j] == true) // color cannot be changed
            {
                ++j;
                --i;
            }
            else // color can be chaged
            {
                answer_table[i][j] = target_color;
                ++i;
                if (i == height && j < width - 1)
                {
                    --i;
                    ++j;
                }
            }
        }
    }

    for (int i(0); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if(answer_table[j][i] == target_table[j][i]) // same color
            {
                fixed_table[j][i] = true;
            }
            else if (j == height - 1) // wrong color
            {
                i = width;
                break;
            }
            else
            {
                break;
            }
        }
    }

    tmp_int = leastUnfixed(fixed_table, height, width); // the target
    target_color = target_table[tmp_int / width][tmp_int % width];
    //cout << tmp_int << "asdfasdf " << target_color << endl;

    i = 0; j = 0;
    while(i < height && j < width) // painting
    {
        if (j == width - 1 && i == height - 1) // at the down-right point
        {
            //cout << "break";
            break;
        }

        if (j == width - 1 || i == 0) // no need to care about color
        {
            ++i;
            continue;
        }
        else
        {
            if (fixed_table[i][j] == true) // color cannot be changed
            {
                ++j;
                --i;
            }
            else // color can be chaged
            {
                answer_table[i][j] = target_color;
                ++i;
                if (i == height && j < width - 1)
                {
                    --i;
                    ++j;
                }
            }
        }
    }

    for (int i(0); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if(answer_table[j][i] == target_table[j][i]) // same color
            {
                fixed_table[j][i] = true;
            }
            else if (j == height - 1) // wrong color
            {
                i = width;
                break;
            }
            else
            {
                break;
            }
        }
    }

    tmp_int = leastUnfixed(fixed_table, height, width); // the target
    target_color = target_table[tmp_int / width][tmp_int % width];
    //cout << tmp_int << "asdfasdf " << target_color << endl;

    i = 0; j = 0;
    while(i < height && j < width) // painting
    {
        if (j == width - 1 && i == height - 1) // at the down-right point
        {
            //cout << "break";
            break;
        }

        if (j == width - 1 || i == 0) // no need to care about color
        {
            ++i;
            continue;
        }
        else
        {
            if (fixed_table[i][j] == true) // color cannot be changed
            {
                ++j;
                --i;
            }
            else // color can be chaged
            {
                answer_table[i][j] = target_color;
                ++i;
                if (i == height && j < width - 1)
                {
                    --i;
                    ++j;
                }
            }
        }
    }

    for (int i(0); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if(answer_table[j][i] == target_table[j][i]) // same color
            {
                fixed_table[j][i] = true;
            }
            else if (j == height - 1) // wrong color
            {
                i = width;
                break;
            }
            else
            {
                break;
            }
        }
    }

    // Display cell_table
    cout << "\nColor: (Target)" << endl;
    printTable(target_table, height, width);

    cout << "\nColor: (Answer)" << endl;
    printTable(answer_table, height, width);

    cout << "\nFixed: (Answer)" << endl;
    printTable(fixed_table, height, width);

    cout << "\nTable Index:" << endl;
    for (int i(0); i < height; ++i)
    {
        for (int j(0); j < width; ++j)
        {
            cout << indexToCcc(i, j, height, width) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    cout << leastUnfixed(fixed_table, height, width) << endl;
    tmp_int = leastUnfixed(fixed_table, height, width);
    cout << tmp_int / width << tmp_int % width << endl;

    // Delete memory allocated for cell_table
    for (int i(0); i < height; ++i)
    {
        delete [] target_table[i];
        delete [] answer_table[i];
        delete [] fixed_table[i];
    }
    delete [] target_table;
    delete [] answer_table;
    delete [] fixed_table;

    return 0;
}
