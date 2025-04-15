#include <iostream>
#include <vector>
using namespace std;

namespace Humming {
    int calculateParity(const std::vector<int> &vec, int bitNumber) {
        int sum = 0;

        for (int i = bitNumber - 1; i < vec.size(); i += 2 * bitNumber) {
            for (int j = i; j < i + bitNumber && j < vec.size(); j++) {
                sum += vec[j];
            }
        }

        sum -= vec[bitNumber - 1];

        return sum % 2;
    }


};
