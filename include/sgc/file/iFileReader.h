#include <string>

namespace sgc {

class IFileReader {
public:
    virtual std::string getFileContent() const = 0;

    virtual ~IFileReader() {};
};

}