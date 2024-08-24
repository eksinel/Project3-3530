#ifndef FIT_CHECK_HPP
#define FIT_CHECK_HPP

#include <vector>

class FitCheck {
public:
    FitCheck(const std::vector<double>& itemSizes_, int numOfSizes_, bool online_);

    std::vector<std::vector<double>> computeBruteForce();

    std::vector<std::vector<double>> computeFirstFit();
    std::vector<std::vector<double>> computeNextFit();
    std::vector<std::vector<double>> computeBestFit();
private:
    const std::vector<double>& itemSizes;
    int numOfSizes;
    bool online;
};

#endif // FIT_CHECK_HPP
