#include <iostream>
#include <vector>
#include "utils.h"
#include "hamming.h"

using namespace std;

vector<int> getInput(int inputSize) {
    vector<int> input(inputSize);
    for(int i = 0; i < inputSize; i++) {
        cin >> input[i];
    }

    return input;
}

vector<int> parseString(const std::string &input) {
    vector<int> result;
    for (char c : input) {
        if (c == '0') {
            result.push_back(0);
        } else {
            result.push_back(1);
        }
    }

    return result;
}

// (15, 11) hamming code
int main() {
    // vector<int> input = getInput(11);
    // vector<int> input = {1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1};
    vector<int> input = parseString("10011100101");

    vector<int> encodedInput = Hamming::encode(input);

    Utils::printVector(encodedInput);
    cout << "100111010100100" << endl;

    return 0;
}
