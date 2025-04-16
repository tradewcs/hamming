#include <iostream>
#include <vector>
#include "utils.h"
#include "hamming.h"
#include <cstdlib>

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
    system("clear");
    // vector<int> input = getInput(11);
    //vector<int> input = parseString("00110001110");
    vector<int> input = parseString("100101");
    cout << "Вхідні дані:      ";
    Utils::printVector(input);
    cout << endl;


    vector<int> encodedInput = Hamming::encode(input);
    cout << "Код Хеммінга:     ";
    Utils::printVector(encodedInput);

    vector<int> parityBits(Hamming::getParityBitsCount(input.size()));
    int k = 0;
    cout << "                  ";
    for (int i = 0; i < encodedInput.size(); i++) {
        if (Hamming::isParityBit(input.size(), i)) {
            parityBits[k++] = encodedInput[i];
            cout << "p";
        } else {
            cout << " ";
        }
    }
    cout << endl << endl;


    cout << "Біти парності:    ";
    Utils::printVector(parityBits);

    cout << endl << "Перевернути біт № ";
    int erorrIndex;
    cin >> erorrIndex;

    while (erorrIndex < 0 || erorrIndex >= encodedInput.size()) {
        cout << "Введіть коректний індекс: ";
        cin >> erorrIndex;
    }
    encodedInput[erorrIndex] = !encodedInput[erorrIndex];
    
    cout << endl << "Код з помилкою:   ";
    Utils::printVector(encodedInput);

    cout << "                  ";
    int i = 0;
    while (i < erorrIndex) {
        cout << " ";
        i++;
    }
    cout << "e" << endl;

    int errorIndex = Hamming::findErrorIndex(encodedInput);
    cout << endl << "Помилка в біті №  " << errorIndex << endl << endl;

    std::vector<int> decodedData = Hamming::decode(encodedInput);
    cout << "Декодовані дані:  ";
    Utils::printVector(decodedData);

    return 0;
}
