#include <stdexcept>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>

#include <sgc/PDFReader.h>

sgc::PDFReader::PDFReader(const std::string& path) {
    document = poppler::document::load_from_file(path);
    if (!document) {
        throw std::runtime_error("Erro ao carregar o arquivo PDF.");
    }
}

sgc::PDFReader::~PDFReader() {
    delete document;
}

std::string sgc::PDFReader::getPDFContent() const {
    // Extrair texto de cada página do PDF
    const int numPages = document->pages();
    std::string content;
    for (int pageNum = 0; pageNum < numPages; ++pageNum) {
        poppler::page* page = document->create_page(pageNum);
        std::string text = page->text().to_latin1().c_str();
        content += text;

        delete page;
    }

    return content;
}