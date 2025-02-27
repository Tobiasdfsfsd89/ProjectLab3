#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

void convertBinaryTextToPDF(const std::string& inputFilePath, const std::string& outputFilePath) {

    std::ifstream inputFile(inputFilePath);
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file: " << inputFilePath << std::endl;
        return;
    }

    std::string binaryString;
    inputFile >> binaryString;
    inputFile.close();

    if (binaryString.size() % 8 != 0) {
        std::cerr << "Error: Binary data length is not a multiple of 8, possibly corrupted." << std::endl;
        return;
    }

    std::vector<unsigned char> buffer;
    for (size_t i = 0; i < binaryString.size(); i += 8) {
        std::bitset<8> byte(binaryString.substr(i, 8));
        buffer.push_back(static_cast<unsigned char>(byte.to_ulong()));
    }

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file: " << outputFilePath << std::endl;
        return;
    }

    outputFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    outputFile.close();

    std::cout << "Conversion complete. PDF restored to: " << outputFilePath << std::endl;
}

int main() {
    std::string inputText = "output.txt";
    std::string outputPDF = "output.epub";

    convertBinaryTextToPDF(inputText, outputPDF);

    return 0;
}
