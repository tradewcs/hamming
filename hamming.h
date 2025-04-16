#include <iostream>
#include <vector>

namespace Hamming {
    int getParityBitsCount(int bitsCount) {
        int parityBitsCount = 0;
        while ((1 << parityBitsCount) < bitsCount + parityBitsCount + 1) {
            parityBitsCount++;
        }

        return parityBitsCount;
    }

    bool isParityBit(int bitsCount, int position) {
        int parityBitsCount = getParityBitsCount(bitsCount);
        for (int i = 0; i < parityBitsCount; i++) {
            int parityIndex = (1 << i) - 1;
            if (parityIndex == position) {
                return true;
            }
        }

        return false;
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
                // std::cout << std::endl;
                // std::cout << "sum += " << "vec[" << j << "]" << " = " << vec[j] << std::endl;
            }
        }

        sum -= vec[bitNumber - 1];

        return sum % 2;
    }

    std::vector<int> getHaffmanTemplate(const std::vector<int> &data) {
        int parityBitsCount = getParityBitsCount(data.size());
        int totalBitsCount = data.size() + parityBitsCount;
        std::vector<int> templateEncoded(totalBitsCount);

        int i = 0;
        int j = 0;
        while (i < totalBitsCount) {
            if (isParityBit(data.size(), i)) {
                templateEncoded[i] = 0;
            } else {
                templateEncoded[i] = data[j];
                j++;
            }

            i++;
        }

        return templateEncoded;
    }

    std::vector<int> encode(const std::vector<int> &data) {
        int parityBitsCount = getParityBitsCount(data.size());
        std::vector<int> parityBits(parityBitsCount);

        std::vector<int> encodedData = getHaffmanTemplate(data);
        for (int i = 0; i < parityBitsCount; i++) {
            int position = (1 << i);

            int parity = Hamming::calculateParity(encodedData, position);
            // std::cout << "position = " << position << "; " << "parity = " << parity << std::endl;
            
            parityBits[i] = parity;
            encodedData[position - 1] = parity;
        }
        // std::cout << std::endl;

        return encodedData;
    }

    std::vector<int> getParityBits(const std::vector<int> &data) {
        int parityBitsCount = getParityBitsCount(data.size());
        std::vector<int> parityBits(parityBitsCount);

        std::vector<int> encodedData = getHaffmanTemplate(data);
        for (int i = 0; i < parityBitsCount; i++) {
            int position = (1 << i) - 1;

            int parity = Hamming::calculateParity(encodedData, position);
            parityBits[i] = parity;
            encodedData[position] = parity;
        }

        return parityBits;
    }

    int findErrorIndex(const std::vector<int> &encodedData) {
        std::vector<int> parityBits(getParityBitsCount(getDataMinSize(encodedData.size())));
        int parityBitsCount = parityBits.size();

        std::vector<int> decodedData(encodedData);
        int errorSum = 0;
        for (int i = 0; i < parityBitsCount; i++) {
            int position = 1 << i;
            parityBits[i] = Hamming::calculateParity(encodedData, position);

            if (parityBits[i] != encodedData[position - 1]) {
                errorSum += position;
            }
        }

        return errorSum - 1;
    }

    std::vector<int> decode(const std::vector<int> &encodedData) {
        std::vector<int> decodedData(encodedData);
        int errorIndex = findErrorIndex(encodedData);
        decodedData[errorIndex] ^= 1;

        return decodedData;
    }
};
