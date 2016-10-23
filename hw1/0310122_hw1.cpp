/**
 * @filename 0310122_hw1.cpp
 * @author   Yanjia Huang <yanjia.huang.tw@gmail.com>
 * @version  2016-10-18
 */

//#include <iostream>
//#include <ctime>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void insertionSort(vector<int>& arr, int low, int high);
void merge(vector<int>& arr, int low, int pivot, int high);
void mergeSort(vector<int>& arr, int low, int high);
void heapify(vector<int>& arr, int n, int i);
void heapSort(vector<int>& arr, int n);
void quickSort(vector<int>& arr, int low, int high);

int main (int __attribute__((unused)) argc, char ** argv) {

    // Execution time test: start
    //clock_t start(clock());

    // declare file I/O stream
    ifstream inFile(argv[2]);
    ofstream outFile(argv[3]);

    // check the input file is open successfully
    if (!inFile.is_open()) {
        exit(1);
    }

    // use vector<int> to store input data
    vector<int> arr;

    // read the data from input file into arr
    int temp(0);
    while (inFile >> temp) {
        arr.push_back(temp);
    }

    // get the vector's size
    const int arr_size(arr.size());

    srand(time(NULL));

    if (argv[1] == static_cast<string>("1")) {        // insertion sort
        insertionSort(arr, 0, arr_size - 1);
    } else if (argv[1] == static_cast<string>("2")) { // merge sort
        mergeSort(arr, 0, arr_size - 1);
    } else if (argv[1] == static_cast<string>("3")) { // heap sort
        heapSort(arr, arr_size);
    } else if (argv[1] == static_cast<string>("4")) { // quick sort
        quickSort(arr, 0, arr_size - 1);
    }

    // write the data in arr into output file
    outFile << arr[0];
    for (int i(1); i < arr_size; ++i) {
        outFile << " " << arr[i];
    }

    // close the input and output file stream
    inFile.close();
    outFile.close();

    // Execution time test: end
    //clock_t end(clock()); cout << "\033[1;33m" << argv[1] << " Exec time: " << "\033[1;31m" << static_cast<double>(end - start) << "\033[0m\n";

    return 0;
}

void insertionSort(vector<int>& arr, int low, int high) {
    int temp(0);
    int length(high + 1), i(low), j(0);
    for (j = 1; j < length; ++j) {
        temp = arr[j];
        i = j - 1;
        while(arr[i] > temp && i >= 0) {
            arr[i + 1] = arr[i];
            --i;
        }
        arr[i + 1] = temp;
    }

    return;
}

void merge(vector<int>& arr, int low, int pivot, int high) {
    int n_1(pivot - low + 1), n_2(high - pivot);
    int L[n_1 + 1], R[n_2 + 1];

    for (int i(0); i < n_1; ++i) {
        L[i] = arr[low + i];
    }

    for (int j(0); j < n_2; ++j) {
        R[j] = arr[pivot + 1 + j];
    }

    int i(0), j(0), n(0);

    while (i != n_1 && j != n_2) {
        if (L[i] > R[j]) {
            arr[low + n] = R[j];
            ++j;
        } else {
            arr[low + n] = L[i];
            ++i;
        }
        ++n;
    }

    while (j != n_2) {
        arr[low + n] = R[j];
        ++j;
        ++n;
    }

    while (i != n_1) {
        arr[low + n] = L[i];
        ++i;
        ++n;
    }

    return;
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (high > low) {
        // divide
        int pivot((low + high) / 2); // choose pivot

        // conquer
        mergeSort(arr, low, pivot); // do merge sort on left hand side array
        mergeSort(arr, pivot + 1, high); // do merge sort on right hand side array

        // combine
        merge(arr, low, pivot, high); // combine two sorted arrays
    }

    return;
}

void heapify(vector<int>& arr, int n, int i) {
    int largest(i);  // Initialize largest as root
    int l(2 * i + 1);  // left = 2 * i + 1
    int r(2 * i + 2);  // right = 2 * i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }

    return;
}

void heapSort(vector<int>& arr, int n) {
    for (int i(n / 2 - 1); i >= 0; --i) { // Build heap
        heapify(arr, n, i);
    }

    for (int i(n - 1); i >= 0; --i) { // extract element from heap
        swap(arr[0], arr[i]); // move root to end
        heapify(arr, i, 0); // heapify the reduced heap
    }

    return;
}

void quickSort(vector<int>& arr, int low, int high) {
    // always choose the last element in arr as pivot
    //int i(low), j(high), pivot(arr[(low + high) / 2]);

    // randomly choose the pivot if the size of arr > 50
    if ((high - low) > 50) {
        int random_num(low + rand() % (high - low + 1));
        swap(arr[random_num], arr[(low + high) / 2]);
    }

    int i(low), j(high), pivot(arr[(low + high) / 2]);

    // divide
    while (i <= j) {
        while (arr[i] < pivot) {
            ++i;
        }

        while (arr[j] > pivot) {
            --j;
        }

        if (i <= j) {
            swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    // conquer
    if (j > low) {
        quickSort(arr, low, j);
    }

    if (i < high) {
        quickSort(arr, i, high);
    }

    // no need to combine

    return;
}
