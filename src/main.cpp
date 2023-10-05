#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <termios.h>
#include <cctype>

#include <sgc/operator.h>
#include <sgc/PDFReader.h>
#include <sgc/cryptoManager.h>
#include <sgc/pemManipulator.h>

#include <libcryptosec/certificate/CertificateRequest.h>
#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/certificate/CertPathValidator.h>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/MessageDigest.h>

struct Answer {
    sgc::Operator op;
    char answer;
};

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

    MessageDigest::loadMessageDigestAlgorithms();

    std::cout << "Quantos operadores irão participar desta decisão?\n";
    int numOperators;
    std::cin >> numOperators;
    std::cin.ignore(1, '\n');
    std::cout << '\n';

    std::vector<sgc::Operator> operators;
    sgc::CryptoManager manager;
    for (int i = 0; i < numOperators; i++) {
        std::cout << "Operador número " << i + 1 << ", insira seus dados\n";
        std::cout << "Nome: ";
        std::string name;
        getline(cin, name);

        std::cout << "CPF (somente números): ";
        std::string cpf;
        std::cin >> cpf;

        std::cout << "E-mail: ";
        std::string email;
        std::cin >> email;
        std::cin.ignore(1, '\n');

        sgc::Operator op(name, cpf, email);
        manager.setOperator(op);
        operators.push_back(op);
    }

    std::cout << "Operadores cadastrados:\n";
    for (int i = 0; i < numOperators; i++) {
        std::cout << "Operador número " << i + 1 << '\n';
        operators[i].printData();
        std::cout << '\n';
    }

    const std::string pdfFilePath = argv[1];

    try {
        sgc::PDFReader pdfReader(pdfFilePath);
        std::string pdfContent = pdfReader.getFileContent();
        std::cout << pdfContent << '\n';

        MessageDigest md(MessageDigest::SHA256);
        md.init(MessageDigest::SHA256);
        md.update(pdfContent);
    }

    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    sgc::Operator luan(
        "Luan Moraes",
        "13397819997",
        "luansmoraes13@gmail.com"
    );

    for (int i = 0; i < operators.size(); i++) {
        std::string opId = operators[i].getId();
        manager.setOpId(opId);
        Certificate opCert = manager.getOpCertificate();
        Certificate caCert = manager.getCaCertificate();

        std::vector<Certificate> untrustedChain(1, opCert);
        std::vector<Certificate> trustedChain(1, caCert);
        CertPathValidator validator(opCert, untrustedChain, trustedChain);
        std::cout << validator.verify() << '\n';
    }

    return 0;
}