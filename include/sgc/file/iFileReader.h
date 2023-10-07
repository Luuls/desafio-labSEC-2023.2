#pragma once

#include <string>

namespace sgc {

// \brief Classe interface para leitura de arquivos
class IFileReader {
public:
    virtual std::string getFileContent() const = 0;

    virtual ~IFileReader() {};
};

}