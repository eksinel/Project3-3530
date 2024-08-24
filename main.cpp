#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "sort.hpp"
#include "fitCheck.hpp"

using namespace std;

int main() {
  ifstream inputFile("items.txt");
  if (!inputFile.is_open()) {
    cerr << "Failed to open the input file." << endl;
    return 1;
  }

  vector<double> itemSizes;
  string line;
  double size;
  int numOfSizes = 0;

  while (getline(inputFile, line)) {
    size = stod(line);
    itemSizes.push_back(size);

    numOfSizes++;
  }
  inputFile.close();

  cout << "Total items: " << numOfSizes << endl;
  cout << "Policy              | Total Bins Used" << endl;
  cout << "--------------------|-----------------" << endl;

  FitCheck onlineFit(itemSizes, numOfSizes, true);
  vector<vector<double>> bins_bruteForce = onlineFit.computeBruteForce();
  vector<vector<double>> bins_ff_on = onlineFit.computeFirstFit();
  vector<vector<double>> bins_nf_on = onlineFit.computeNextFit();
  vector<vector<double>> bins_bf_on = onlineFit.computeBestFit();

  vector<double> sortedItemSizes = itemSizes;
  quickSort(sortedItemSizes);
  FitCheck offlineFit(sortedItemSizes, numOfSizes, false);
  vector<vector<double>> bins_ff_off = offlineFit.computeFirstFit();
  vector<vector<double>> bins_bf_off = offlineFit.computeBestFit();

  cout << "\n" << "Optimal:" << endl;
  displayBins(bins_bruteForce);
  cout << "\n" << "Online - First Fit:" << endl;
  displayBins(bins_ff_on);
  cout << "\n" << "Online - Next Fit:" << endl;
  displayBins(bins_nf_on);
  cout << "\n" << "Online - Best Fit:" << endl;
  displayBins(bins_bf_on);
  cout << "\n" << "Offline - First Fit:" << endl;
  displayBins(bins_ff_off);
  cout << "\n" << "Offline - Best Fit:" << endl;
  displayBins(bins_bf_off);

  cout << endl;

  return 0;
}
