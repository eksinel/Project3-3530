#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <algorithm>

// Quicksort Algorithm
// Array is sorted in-place
// A vector of integers is passed by reference
void quickSort(std::vector<double>& arr);

// Code for displaying bins
// I didn't want to make another hpp and cpp file just for this
void displayBins(const std::vector<std::vector<double>> bins);

#endif // SORT_HPP
