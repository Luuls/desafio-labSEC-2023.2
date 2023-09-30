#include <string>

#include <poppler/cpp/poppler-document.h>

namespace sgc {

class PDFReader {
public:
    PDFReader(const std::string& path);
    ~PDFReader();

    std::string getPDFContent() const;

private:
    poppler::document* document;
};

}