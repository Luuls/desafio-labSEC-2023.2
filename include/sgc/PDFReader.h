#pragma once

#include <string>

#include <sgc/file/iFileReader.h>

#include <poppler/cpp/poppler-document.h>

namespace sgc {

class PDFReader : public IFileReader {
public:
    PDFReader(const std::string& path);
    virtual ~PDFReader();

    virtual std::string getFileContent() const;

private:
    poppler::document* document;
};

}