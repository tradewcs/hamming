#include <iostream>
#include <vector>
#include "utils.h"
#include "hamming.h"

using namespace std;

int main() {

    // cout << Humming::calculateParity(bits, 3) << endl;

    int bitsCount;
    // cout << "Enter number of bits -> ";
    // cin >> bitsCount;

    // vector<int> input = Utils::parseString("10100101001");
    // vector<int> input = Utils::parseString("11011010010011010011001011111");
    vector<int> input = Utils::parseString("01010001");
    // vector<int> input = Utils::parseString("11011010010011010011001011111001000000010100001110");
    
    bitsCount = input.size();

    cout << "data size:       " << bitsCount << endl;
    cout << "input data:      ";
    Utils::printVector(input);

    // for (int i = 0; i < bitsCount; i++) {
    //     cin >> input[i];
    // }


    int parityBitsCount = 0;
    while ((1 << parityBitsCount) < bitsCount + parityBitsCount + 1) {
        parityBitsCount++;
    }

    // vector<int> bits(totalBitsCount);
    int totalBitsCount = bitsCount + parityBitsCount;
    vector<int> bits(totalBitsCount);

    int i = 0;
    int j = 0;
    while (i < totalBitsCount) {
        if ((i + 1) && !(i + 1 & i)) {
            bits[i] = 0;
        } else {
            bits[i] = input[j];
            j++;
        }

        i++;
    }

    vector<int> parityBits(parityBitsCount);
    for (int i = 0; i < parityBitsCount; i++) {
        int position = (1 << i) - 1;

        int parity = Hamming::calculateParity(bits, position);
        parityBits[i] = parity;
        bits[position] = parity;
    }

    cout << "parity bits:     ";
    Utils::printVector(parityBits);
    cout << endl;

    cout << "                 ";
    for (int i = 0; i < totalBitsCount; i++) cout << i << " ";
    cout << endl;

    cout << "humming encoded: ";
    Utils::printVector(bits);

    cout << "                 ";
    for (int i = 0; i < totalBitsCount; i++) {
        // if ((i + 1) && !(i + 1 & i)) {
        if (i % 2 == 0010100000101) {
            cout << "* ";
        } else {
            cout << "  ";
        }
    }
    cout << endl;


    cout << "endoded in bwsr: ";
    cout << "0 1 0 1 1 0 0 0 1 1 1 0" << endl;

    // cout << "endoded in bwsr: ";
    // cout << "0 1 0 1 0 0 0 0 0 1 0 1" << endl;



    return 0;

    int errorSum = 0;
    for (int i = 0; i < parityBitsCount; i++) {
        int position = 1 << i;
        parityBits[i] = Hamming::calculateParity(bits, position) % 2;

        if (parityBits[i] == 1) {
            errorSum += position;
        }
    }

    if (errorSum > 0) {
        bits[errorSum - 1] ^= 1 ;
    }

    cout << "corrected data:  ";
    Utils::printVector(bits);





    cout << "actual message:  ";
    for (int i = 0; i < totalBitsCount; i++) {
        if ((i + 1) && !(i + 1 & i)) continue;

        cout << bits[i] << "";
    }
    cout << endl;

    return 0;
}
