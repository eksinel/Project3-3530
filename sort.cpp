#include "sort.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int partition(vector<double>& arr, int front, int end) {
    int pos = front;
    for (int i = front; i < end; i++) {
        if (arr.at(i) > arr.at(end)) {
            swap(arr[i], arr[pos]);
            pos++;
        }
    }
    swap(arr[end], arr[pos]);
    return pos;
};

void quickSortRecurs(vector<double>& arr, int front, int end) {
    if (front < end) {
        int pos = partition(arr, front, end);
        quickSortRecurs(arr, front, pos-1);
        quickSortRecurs(arr, pos+1, end);
    }
};

void quickSort(vector<double>& arr) 
{
    int end = arr.size()-1;
    int pos = partition(arr, 0, end);
    quickSortRecurs(arr, 0, pos-1);
    quickSortRecurs(arr, pos+1, end);
}

void displayBins(const vector<vector<double>> bins) {
    int numBins = 0;
    for (auto& bin : bins) {
        cout << "Bin " << numBins << ": "; 
        int binSize = bin.size();
        for (double item : bin) {
            binSize--;
            cout << fixed << setprecision(2) << item;
            if (binSize != 0) {
                cout << ", ";
            }
        }
        cout << endl;
        numBins++;
    }
}