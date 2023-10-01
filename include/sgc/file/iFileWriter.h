#include <string>

namespace sgc {

class IFileWriter {
public:
    virtual void writeFile(const std::string& content) const = 0;

    virtual ~IFileWriter() {};
};

}