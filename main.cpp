#include <iostream>
#include <vector>
#include "utils.h"
#include "hamming.h"

using namespace std;

vector<int> getInput(int inputSize) {
    vecor<int> input(inputSize);
    for(int i = 0; i < inputSize; i++) {
        cin >> input[i];
    }

    return input;
}

// (15, 11) hamming code
int main() {
    vector<int> input = getInput(11);

    vector<int> encodedBIts = Hamming::encode(input);

    return 0;
}
