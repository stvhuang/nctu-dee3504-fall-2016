#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_PHONE(100);
const int MAX_DROP(63);
const int MAX_CASE(20);

int timespec_diff_us(timespec& t1, timespec& t2)
{
    return (t2.tv_sec - t1.tv_sec) * 1e6 + (t2.tv_nsec - t1.tv_nsec) / 1e3;
}

void buildMaxFloor(long long int maxFloor[][MAX_DROP + 1], int MAX_PHONE_IN_INPUT)
{
    // terminal condition
    for (int i(0); i <= MAX_PHONE_IN_INPUT; ++i)
    {
        maxFloor[i][1] = 1;
    }
    for (int i(0); i <= MAX_DROP; ++i)
    {
        maxFloor[1][i] = i;
    }

    // build maxFloor table
    for (int i(2); i <= MAX_PHONE_IN_INPUT; ++i)
    {
        for (int j(2); j <= MAX_DROP; ++j)
        {
            maxFloor[i][j] = 1 + maxFloor[i - 1][j - 1] + maxFloor[i][j - 1];
        }
    }
}

int findLeastDrop(long long int maxFloor[][MAX_DROP + 1], long long int eggs, long long int floors, ofstream & outFile)
{
        for (int i(1); i <= MAX_DROP; ++i)
        {
            if (maxFloor[eggs][i] >= floors)
            {
                outFile << i << "\n";
                return i;
            }
        }
        outFile << "More then 63 times needed\n";
        return 0;
}

void findBestStep(long long int maxFloor[][MAX_DROP + 1], long long int eggs, int leastDrop, ofstream & outFile)
{
    long long sum(0);
    for (int i(leastDrop - 1); i >= 0; --i)
    {
        sum += 1 + maxFloor[eggs - 1][i];
        outFile << sum << " ";
    }
    outFile << "\n";
}

int main(int argc, char** argv)
{
    timespec time_begin, time_end; int ExecTime; clock_gettime(CLOCK_REALTIME, &time_begin);

    long long int testCase[MAX_CASE][2];
    long long int maxFloor[MAX_PHONE + 1][MAX_DROP + 1];
    int LAST_CASE(0);
    int MAX_PHONE_IN_INPUT(0);
    int leastDrop(0);

    ifstream inFile(argv[2]);
    ofstream outFile(argv[3]);
    if (!inFile.is_open())
    {
        cout << "Can't find inputfile!" << endl;
        return -1;
    }

    // scan testCase
    for (int i(0); i < MAX_CASE; ++i)
    {
        inFile >> testCase[i][0] >> testCase[i][1];
        if (testCase[i][0] == 0)
        {
            LAST_CASE = i;
            break;
        }

        if (testCase[i][0] > MAX_PHONE_IN_INPUT)
        {
            MAX_PHONE_IN_INPUT = testCase[i][0];
        }
    }

    { // DP solution
        // build the bottom-up table
        buildMaxFloor(maxFloor, MAX_PHONE_IN_INPUT);
        for (int i(0); i < LAST_CASE; ++i)
        {
            leastDrop = findLeastDrop(maxFloor, testCase[i][0], testCase[i][1], outFile);
            if (leastDrop != 0)
            {
                findBestStep(maxFloor, testCase[i][0], leastDrop, outFile);
            }
        }
    }

    if (atoi(argv[1]) == 1)
    { // Recursive solution
    }

    // close file stream
    inFile.close();
    outFile.close();

    clock_gettime(CLOCK_REALTIME, &time_end); ExecTime = timespec_diff_us(time_begin, time_end); cout << "\nExecTime = " <<  ExecTime << "us" << endl;
    return 0;
}
