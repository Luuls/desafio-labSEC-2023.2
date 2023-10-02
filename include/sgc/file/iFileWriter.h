#pragma once

#include <string>

namespace sgc {

class IFileWriter {
public:
    virtual void writeToFile(const std::string& content) const = 0;

    virtual ~IFileWriter() {};
};

}
