#include <iostream>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-document.h>

#include <sgc/operator.h>

#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/SymmetricCipher.h>

int main(int argc, char** argv) {
    std::string usage = "Uso: " + std::string(argv[0]) + " <caminho do PDF>";
    if (argc < 2) {
        std::cerr << usage << '\n';
        return 1;
    }

    else if (argc > 2) {
        std::cerr << "Erro: muitos argumentos." << '\n';
        std::cerr << usage << '\n';
        return 1;
    }

    const std::string pdfFilePath = argv[1];

    // Abrir o documento PDF
    poppler::document* pdfDocument = poppler::document::load_from_file(pdfFilePath);
    
    if (!pdfDocument) {
        std::cerr << "Erro ao abrir o arquivo PDF." << std::endl;
        return 1;
    }

    // Extrair texto de cada página do PDF
    const int numPages = pdfDocument->pages();
    for (int pageNum = 0; pageNum < numPages; ++pageNum) {
        poppler::page* page = pdfDocument->create_page(pageNum);
        std::string text = page->text().to_latin1();
        std::cout << text << '\n';
    }

    // RSAKeyPair pair(2048);
    // std::cout << pair.getPrivateKey()->getPemEncoded() << '\n';

    return 0;
}