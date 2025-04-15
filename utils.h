#include <iostream>
#include <vector>
#include <string>

namespace Utils {
    int countElements(const std::vector<int> &vec, int target) {
        int count = 0;
        for (int el : vec) {
            if (el == target) {
                count++;
            }
        }

        return count;
    }

    void printVector(const std::vector<int> &vec) {
        for (int el : vec) {
            std::cout << el << "";
        }
        std::cout << std::endl;
    }
    
    std::vector<int> parseString(std::string str) {
        std::vector<int> res;
        for (char c : str) {
            if (c == '0') {
                res.push_back(0);
            } else {
                res.push_back(1);
            }
        }

        return res;
    }
};