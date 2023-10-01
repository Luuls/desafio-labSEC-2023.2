#include <iostream>
#include <string>

#include <sgc/file/fileReader.h>
#include <sgc/file/fileWriter.h>

namespace sgc {

class FileManipulator : public FileReader, public FileWriter {
public:
    virtual ~FileManipulator() {};
};

}