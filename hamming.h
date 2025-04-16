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
    int getParityBitsCount(int bitsCount) {
        int parityBitsCount = 0;
        while ((1 << parityBitsCount) < bitsCount + parityBitsCount + 1) {
            parityBitsCount++;
        }

        return parityBitsCount;
    }

    int getBitsCountFromParity(int parityBitsCount) {
        int bitsCount = 0;
        while (getParityBitsCount(bitsCount) < parityBitsCount) {
            bitsCount++;
        }

        return bitsCount;
    }

    int getDataMinSize(int encodedSize) {
        int dataSize = 0;
        while (dataSize + getParityBitsCount(dataSize) < encodedSize) {
            dataSize++;
        }

        return dataSize;
    }

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

    std::vector<int> getHaffmanTemplate(const std::vector<int> &data) {
        int totalBitsCount = getParityBitsCount(data.size());
        std::vector<int> template(data.size() + totalBitsCount);

        int i = 0;
        int j = 0;
        while (i < totalBitsCount) {
            if ((i + 1) && !(i + 1 & i)) {
                template[i] = 0;
            } else {
                template[i] = data[j];
                j++;
            }

            i++;
        }

        return template;
    }

    std::vector<int> encode(const std::vector<int> &data) {
        int parityBitsCount = gettParityBitsCount(data);
        vector<int> parityBits(parityBitsCount);

        std::vector<int> encodedData = getHaffmanTemplate(data);
        for (int i = 0; i < parityBitsCount; i++) {
            int position = (1 << i) - 1;

            int parity = Hamming::calculateParity(encodedData, position);
            parityBits[i] = parity;
            encodedData[position] = parity;
        }

        return encodedData;
    }

    std::vector<int> getParityBits(const std::vector<int> &data) {
        int parityBitsCount = gettParityBitsCount(data);
        vector<int> parityBits(parityBitsCount);

        std::vector<int> encodedData = getHaffmanTemplate(data);
        for (int i = 0; i < parityBitsCount; i++) {
            int position = (1 << i) - 1;

            int parity = Hamming::calculateParity(encodedData, position);
            parityBits[i] = parity;
            encodedData[position] = parity;
        }

        return parityBits;
    }

    std::vector<int> decode(const std::vector<int> &encodedData) {
        std::vector<int> parityBits(getParityBitsCount(getDataMinSize(encodedData.size())));
        int parityBitsCount = parityBits.size();

        std::vector<int> decodedData(encodedData);
        int errorSum = 0;
        for (int i = 0; i < parityBitsCount; i++) {
            int position = (1 << i) - 1;
            parityBits[i] = Hamming::calculateParity(encodedBIts, position);

            if (parityBits[i] != encodedData[position]) {
                errorSum += position + 1;
            }
        }

        if (errorSum > 0) {
            decodedData[errorSum] ^= 1 ;
        }

        return decodedData;
    }
};
