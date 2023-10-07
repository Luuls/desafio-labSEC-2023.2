#pragma once

#include <string>

#include <sgc/file/iFileReader.h>

#include <poppler/cpp/poppler-document.h>

namespace sgc {

// \brief Classe que lê um arquivo PDF
class PDFReader : public IFileReader {
public:
    PDFReader(const std::string& path);
    virtual ~PDFReader();

    // \brief Retorna todo o conteúdo do PDF em uma string
    // \return O conteúdo do PDF
    virtual std::string getFileContent() const;

private:
    poppler::document* document;
};

}