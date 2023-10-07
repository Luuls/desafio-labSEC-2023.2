#pragma once

#include <iostream>
#include <string>

#include <sgc/file/iFileReader.h>
#include <sgc/file/iFileWriter.h>

namespace sgc {

// \brief Classe interface para manipulação de arquivos
class IFileManipulator : public IFileReader, public IFileWriter {
public:
    virtual ~IFileManipulator() {};
};

}