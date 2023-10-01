#include <string>

namespace sgc {

class FileReader {
public:
    virtual std::string getFileContent() const = 0;

    virtual ~FileReader() {};
};

}