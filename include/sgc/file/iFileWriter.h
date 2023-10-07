#pragma once

#include <string>

namespace sgc {

// \brief Classe interface para escrita de arquivos
class IFileWriter {
public:
    virtual void writeToFile(const std::string& content) const = 0;

    virtual ~IFileWriter() {};
};

}
