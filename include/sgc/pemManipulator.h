#pragma once

#include <fstream>
#include <string>

#include <sgc/file/iFileManipulator.h>

namespace sgc {

class PemManipulator : public IFileManipulator {
public:
    PemManipulator(const std::string& path);
    PemManipulator(
        const std::string& inputFilePath,
        const std::string& outputFilePath
    );

    virtual ~PemManipulator();

    virtual std::string getFileContent() const;
    virtual void writeToFile(const std::string& content) const;

    void setInputFilePath(const std::string& path);
    void setOutputFilePath(const std::string& path);
    void setFilePaths(
        const std::string& inputFilePath,
        const std::string& outputFilePath
    );

private:
    std::string inputPath;
    std::string outputPath;
};

}