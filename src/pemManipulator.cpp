#include <cstdlib>

#include <sgc/pemManipulator.h>

sgc::PemManipulator::PemManipulator(const std::string& filePath) :
    inputPath(filePath), outputPath(filePath) {}

sgc::PemManipulator::PemManipulator(
    const std::string& inputFilePath,
    const std::string& outputFilePath
) : inputPath(inputFilePath), outputPath(outputFilePath) {}

sgc::PemManipulator::~PemManipulator() {}

std::string sgc::PemManipulator::getFileContent() const {
    std::ifstream file(this->inputPath.c_str());
    if (!file.good()) {
        throw std::runtime_error("Arquivo " + inputPath + " não encontrado.");
    }

    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }

    file.close();
    return content;
}

void sgc::PemManipulator::writeToFile(const std::string& content) const {
    std::ofstream file;

    // verifica se o arquivo existe
    file.open(this->outputPath.c_str());
    file.close();
    if (!file.good()) {
        size_t lastDirSlash = inputPath.rfind('/');
        std::string dir = inputPath.substr(0, lastDirSlash + 1);
        std::system(("mkdir -p " + dir).c_str());
    }

    file.open(this->inputPath.c_str());
    file.write(content.c_str(), content.size());
    file.close();
    return;
}