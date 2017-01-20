#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

char** target_table(NULL);
char** answer_table(NULL);
bool** fixed_table(NULL);
int width(0), height(0);
vector< vector<int> > answer_lists;
vector<int> answer;

void initialization(char* inuptfile)
{
    ifstream inFile(inuptfile);

    inFile >> width >> height;

    target_table = new char* [height];
    answer_table = new char* [height];
    fixed_table = new bool* [height];
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
            inFile >> target_table[i][width - j - 1];
            answer_table[i][j] = '?';
            fixed_table[i][j] = false;
        }
    }

    inFile.close();
}

int indexToCcc(int i, int j)
{
    return i * width + j + 1;
}

int leastUnfixed(bool** table)
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
                return j * width + i;
            }
        }
    }
    return width * height - 1;
}

bool checkIfDone(bool** fixed_table)
{
    for (int i(1); i < height; ++i)
    {
        for (int j(0); j < width - 1; ++j)
        {
            if (fixed_table[i][j] == false)
            {
                return false;
            }
        }
    }
    return true;
}

void doPrint()
{
    int i(0), j(0);
    int tmp_int = leastUnfixed(fixed_table); // the target
    char target_color = target_table[tmp_int / width][tmp_int % width];
    answer.push_back(static_cast<int>(target_color - '0'));

    while(i < height && j < width) // painting
    {
        if (j == width - 1 && i == height - 1) // at the down-right point
        {
            answer.push_back(indexToCcc(i, j));
            break;
        }
        else if (j == width - 1 || i == 0) // on the edge
        {
            answer.push_back(indexToCcc(i, j));
            ++i;
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
                answer.push_back(indexToCcc(i, j));
                ++i;
                if (i == height && j < width - 1)
                {
                    --i;
                    ++j;
                }
            }
        }
    }

    // First column
    for (int j(height - 1); j > 0; --j)
    {
        if(answer_table[j][0] == target_table[j][0]) // same color
        {
            fixed_table[j][0] = true;
        }
        else
        {
            break;
        }
    }

    // Other columns
    for (int i(1); i < width - 1; ++i)
    {
        for (int j(height - 1); j > 0; --j)
        {
            if(answer_table[j][i] == target_table[j][i] && fixed_table[j][i - 1] == true) // same color and the left one is true
            {
                fixed_table[j][i] = true;
            }
            else
            {
                if (j == (height - 1))
                {
                    i = width;
                }
                break;
            }
        }
    }
}

void ending() // DONE
{
    for (int i(0); i < height; ++i)
    {
        delete [] target_table[i];
        delete [] answer_table[i];
        delete [] fixed_table[i];
    }

    delete [] target_table;
    delete [] answer_table;
    delete [] fixed_table;
}

int main(int argc, char** argv)
{
    // Read file and initialize the arrays
    initialization(argv[1]);

    while (!checkIfDone(fixed_table)) // Not yet done
    {
        answer.clear();
        doPrint();
        answer_lists.push_back(answer);
    }

    ofstream outFile(argv[2]);

    outFile << answer_lists.size() << endl;
    for (int i(0); static_cast<unsigned int>(i) < answer_lists.size(); ++i)
    {
        for (int j(0); static_cast<unsigned int>(j) < answer_lists.at(i).size(); ++j)
        {
            //outFile << setw(3);
            outFile << answer_lists.at(i).at(j) << " ";
        }
        outFile << endl;
    }

    outFile.close();

    // Delete memory allocated for cell_table
    ending();

    return 0;
}
