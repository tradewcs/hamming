#include <iostream>
#include <vector>
using namespace std;

// 00101001              len = 8
// **0*010*1001          len = 12

// 000001001001

// bitNumber = 1
// i = 0
// j = 0 => sum += vec[0]; sum == 0

// i = 2
// j = 2
// sum += vec[2] => sum = 0

// i = 4
// j = 4
// sum += vec[j]; sum = 0

// i = 6
// j = 6
// sum += vec[6] => sum = 1

// i = 8
// j = 8
// sum += vec[8] => sum = 1

// i = 10
// j = 10
// sum += vec[10] => sum = 1

// sum = 1

namespace Hamming {
    int calculateParity(const std::vector<int> &vec, int bitNumber) {
        int sum = 0;

        for (int i = bitNumber - 1; i < vec.size(); i += 2 * bitNumber) {
            for (int j = i; j < i + bitNumber && j < vec.size(); j++) {
                sum += vec[j];
            }
        }

        sum -= vec[bitNumber - 1];

        return sum % 2 != 1;
    }


};
