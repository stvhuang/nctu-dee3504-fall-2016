/**
 * @filename 0310122_hw2.cpp
 * @author   Yanjia Huang <yanjia.huang.tw@gmail.com>
 * @version  2016-11-30
 */

#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

const int CASE_MAX(20);

void buildIphoneDropTable(long long int**, long long int, long long int);
int timespec_diff_us(timespec&, timespec&);
template <class T1, class T2> void print2DMatrix(T1 ** arr, T2 idx1, T2 idx2);

int main(int argc, char** argv)
{
    long long int testCase[CASE_MAX][2];
    long long int num_iphone(0), num_stair(0);
    long long int max_iphone(testCase[0][0]), max_stair(testCase[0][1]);

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    if (!inFile.is_open()) {
        cout << "Can't find inputfile!" << endl;
        return -1;
    }

    for (int i(0); i < CASE_MAX; ++i)
    {
        inFile >> testCase[i][0] >> testCase[i][1];
        if (testCase[i][0] == 0 && testCase[i][1] == 0)
        {
            for (int k(i + 1); k < CASE_MAX; ++k)
            {
                testCase[k][0] = testCase[k][1] = 0;
            }
            break;
        }
    }

    for (int i(0); i < CASE_MAX; ++i) // find max_iphone & max_stair
    {
        if (static_cast<long long int>(log2(testCase[i][1])) < testCase[i][0])
        {
            continue;
        }
        else
        {
            if (testCase[i][0] > max_iphone)
                max_iphone = testCase[i][0];
            if (testCase[i][1] > max_stair)
                max_stair = testCase[i][1];
        }
    }

    cout << "Max # of iPhone: "; cout.width(8); cout << max_iphone << endl;
    cout << "Max # of stair:  "; cout.width(8); cout << max_stair << endl;
    cout << "Number of iPhones: "; cin >> num_iphone;
    cout << "Number of starts:  "; cin >> num_stair;

    // Allocate memory for recording least drop times
    long long int** m = new long long int* [num_iphone + 1];
    for (long long int i(0); i <= num_iphone; ++i)
    {
        m[i] = new long long int[num_stair + 1]();
    }

    //print2DMatrix(m, num_iphone + 1, num_stair + 1);

    long double execTime(0); timespec time_begin, time_end; clock_gettime(CLOCK_REALTIME, &time_begin);

    buildIphoneDropTable(m, num_iphone, num_stair);
    cout << "\033[1;33mAnswer:\t\t\033[1;31m" << m[num_iphone][num_stair] << "\033[0m" << endl;

    clock_gettime(CLOCK_REALTIME, &time_end); execTime = timespec_diff_us(time_begin, time_end); cout << "\033[1;33mExec time:\t\033[1;31m" <<  execTime / 1000 << "\033[0m" << endl;

    //print2DMatrix(m, num_iphone + 1, num_stair + 1);

    //if log2(testCase[i][1]) > testCase[i][0])
/*    if (static_cast<long long int>(log2(num_stair)) < num_iphone)
    {
        int droptimes;
        droptimes = static_cast<long long int>(log2(num_stair)) + 1;
        cout << droptimes << endl;
        for (int i(droptimes - 1); i >= 0; --i)
        {
            printf( "%lld ", static_cast<long long int>(pow(2, droptimes)) - static_cast<long long int>(pow(2, i)) );
            //cout << pow(2, droptimes) - static_cast<long long int>(pow(2, i)) << " ";
        }
        cout << endl;
    }
*/

    // Free the allocated memory
    for (long long int i(0); i <= num_iphone; ++i)
    {
        delete [] m[i];
    }
    delete [] m;

    // close file stream
    inFile.close();
    outFile.close();

    return 0;
}

void buildIphoneDropTable(long long int ** arr, long long int iphone, long long int stair)
{
    long long int i(0), j(0), k(0), tmp(0);//, position[stair] = {0};

    for (i = 1; i <= iphone; ++i)
    {
        arr[i][0] = 0;
        arr[i][1] = 1;
    }

    for (j = 1; j <= stair; ++j)
    {
        arr[0][j] = 0;
        arr[1][j] = j;
    }

    for (i = 2; i <= iphone; ++i)
    {
        for (j = 2; j <= stair; ++j)
        {
            /*** print ***//*
            cout.width(3);
            cout << i;
            cout.width(8);
            cout << j << endl;*/
            /*** print ***/

            arr[i][j] = INT_MAX;
            for (k = 1; k <= j; ++k)
            {
                tmp = 1 + max(arr[i - 1][k - 1], arr[i][j - k]);
                if (tmp < arr[i][j])
                {
                    if (tmp == arr[i][j - 1])
                    {
                        arr[i][j] = tmp;
                        break;
                    }
                    arr[i][j] = tmp;
                }
            }
            //if (arr[i][j] > 64) return;
            /*
            if (arr[i][j] > 64)
            {
                ++i;
                break;
            }*/
            //if (arr[i][j] == i)
            //    position[i]++;
        }
    }
/*
    for (long long int i(0); i < stair; ++i)
    {
        cout.width(2);
        cout << position[i];
    }
*/
    return;
}

int timespec_diff_us(timespec& t1, timespec& t2)
{
    return (t2.tv_sec - t1.tv_sec) * 1e6 + (t2.tv_nsec - t1.tv_nsec) / 1e3;
}

template <class T1, class T2>
void print2DMatrix(T1 ** arr, T2 idx1, T2 idx2)
{
    for (T2 i(0); i < idx1; ++i)
    {
        for (T2 j(0); j < idx2; ++j)
        {
            cout.width(2);
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return;
}
