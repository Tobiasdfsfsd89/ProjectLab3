#include <iostream>
#include <fstream>
#include <vector>

void convertPDFToBinaryText(const std::string& inputFilePath, const std::string& outputFilePath) {

    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file: " << inputFilePath << std::endl;
        return;
    }

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::ofstream outputFile(outputFilePath);
    if (!outputFile) {
        std::cerr << "Error: Unable to open output file: " << outputFilePath << std::endl;
        return;
    }

    for (unsigned char byte : buffer) {
        for (int i = 7; i >= 0; --i) {
            outputFile << ((byte >> i) & 1);
        }
    }

    outputFile.close();
    std::cout << "Conversion complete. Binary data saved to: " << outputFilePath << std::endl;
}

int main() {
    std::string inputPDF = "Random Story.epub";
    std::string outputText = "output.txt";

    convertPDFToBinaryText(inputPDF, outputText);

    return 0;
}
