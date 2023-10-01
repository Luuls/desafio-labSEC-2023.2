#include <string>

namespace sgc {

class FileWriter {
public:
    virtual void writeFile(const std::string& content) const = 0;

    virtual ~FileWriter() {};
};

}