#include "fitCheck.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

FitCheck::FitCheck(const vector<double>& itemSizes_, int numOfSizes_, bool online_)
    : itemSizes(itemSizes_), numOfSizes(numOfSizes_), online(online_) {}

vector<vector<double>> FitCheck::computeBruteForce() {

    // Brute Force Function
    vector<vector<double>> bestBins;
    int bestBinsSize = numeric_limits<int>::max();
    vector<double> permutaionOfItems = itemSizes;
    do {
        FitCheck newFit(permutaionOfItems, numOfSizes, false);
        vector<vector<double>> currentBins = newFit.computeNextFit();
        int currentBinsSize = currentBins.size();
        if (currentBinsSize < bestBinsSize) {
            bestBins = currentBins;
            bestBinsSize = currentBinsSize;
        }
    } while (next_permutation(permutaionOfItems.begin(), permutaionOfItems.end()));
    
    // Display Results
    cout << "Optimal Solution    | " << bestBinsSize << endl;
    return bestBins;
}

vector<vector<double>> FitCheck::computeFirstFit() {

    // First Fit Function
    vector<vector<double>> bins_ff;
    for (double size : itemSizes) {
        bool packed = false;
        for (auto& bin : bins_ff) {
            double currentBinSize = 0.0;
            for (double item : bin) {
                currentBinSize += item;
            }
            currentBinSize += size;
            if (currentBinSize <= 1) {
                bin.push_back(size);
                packed = true;
                break;
            }
        }
        if(!packed) {
            bins_ff.push_back({size});
        }
    }

    // Display Results
    string outConnection = (online) ? "Online - First Fit  | " : "Offline - First Fit | ";
    cout << outConnection << bins_ff.size() << endl;
    return bins_ff;
}

vector<vector<double>> FitCheck::computeNextFit() {

    // Next Fit Function
    vector<vector<double>> bins_nf;
    int index;
    for (int i = 0; i < numOfSizes; i++) {
        if(i == 0) {
            bins_nf.push_back({itemSizes[i]});
            index = 0;
        }
        else {
            double currentBinSize = 0.0;
            for (double item : bins_nf[index]) {
                currentBinSize += item;
            }
            if (currentBinSize + itemSizes[i] <= 1) {
                bins_nf[index].push_back(itemSizes[i]);
            }
            else {
                bins_nf.push_back({itemSizes[i]});
                index++;
            }
        }
    }

    // Display Results
    if (online) {
        cout << "Online - Next Fit   | " << bins_nf.size() << endl;
    }
    return bins_nf;
}

vector<vector<double>> FitCheck::computeBestFit() {

    // Best Fit Function
    vector<vector<double>> bins_bf;
    for (double size : itemSizes) {
        int binSize = bins_bf.size();
        double bestBinSize = 0.0;
        int bestIndex = -1;
        for (int i = 0; i < binSize; i++) {
            double currentBinSize = 0.0;
            for (double item : bins_bf[i]) {
                currentBinSize += item;
            }
            currentBinSize += size;
            if (currentBinSize <= 1 && currentBinSize > bestBinSize) {
                bestBinSize = currentBinSize;
                bestIndex = i;
            }
        }
        if(bestIndex < 0) {
            bins_bf.push_back({size});
        }
        else {
            bins_bf[bestIndex].push_back(size);
        }
    }

    // Display Results
    string outConnection = (online) ? "Online - Best Fit   | " : "Offline - Best Fit  | ";
    cout << outConnection << bins_bf.size() << endl;
    return bins_bf;
}