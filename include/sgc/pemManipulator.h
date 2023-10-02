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

private:
    std::string inputPath;
    std::string outputPath;
};

}