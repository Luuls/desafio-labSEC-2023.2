#include <iostream>
#include <string>

#include <sgc/file/iFileReader.h>
#include <sgc/file/iFileWriter.h>

namespace sgc {

class IFileManipulator : public IFileReader, public IFileWriter {
public:
    virtual ~IFileManipulator() {};
};

}