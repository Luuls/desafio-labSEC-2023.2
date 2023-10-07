#pragma once

#include <fstream>
#include <string>

#include <sgc/file/iFileManipulator.h>

namespace sgc {

// \brief Classe que manipula um arquivo PEM
class PemManipulator : public IFileManipulator {
public:
    PemManipulator(const std::string& path);
    PemManipulator(
        const std::string& inputFilePath,
        const std::string& outputFilePath
    );

    virtual ~PemManipulator();

    // \brief Retorna todo o conteúdo do arquivo PEM em uma string
    virtual std::string getFileContent() const;
    // \brief Escreve uma string em formato PEM no caminho atual guardado no objeto
    // \param content Conteúdo a ser escrito no arquivo
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