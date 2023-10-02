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
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/MessageDigest.h>

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

        // generate certificate and key pair
        RSAKeyPair pair(2048);
        PrivateKey* privateKey = pair.getPrivateKey();
        std::string pemPrivateKey = privateKey->getPemEncoded();
        std::string fileDir = "./data/keys/";
        delete privateKey;

        MessageDigest md(MessageDigest::SHA256);
        md.init(MessageDigest::SHA256);
        // ByteArray cpfBytes(cpf);
        md.update(cpf);
        std::string hash = md.doFinal().toHex();
        for (size_t i = 0; i < hash.length(); i++) {
            hash[i] = std::tolower(hash[i]);
        }

        std::string filePath = fileDir + hash + ".pem";
        sgc::PemManipulator pemManipulator(filePath);
        pemManipulator.writeToFile(pemPrivateKey);
        // std::cout << pemManipulator.getFileContent() << '\n';
        // CertificateRequest request(pair.getPublicKey()->getPemEncoded());
        // request.getPublicKey()->getPemEncoded();
        operators.push_back(sgc::Operator(name, cpf, email));
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
        std::cout << md.doFinal().toHex() << '\n';
    }

    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    std::string cpf0 = "12345678910";
    sgc::CryptoManager manager(cpf0);
    PrivateKey* privateKey = manager.getPrivateKey();
    std::cout << privateKey->getPemEncoded() << '\n';
    delete privateKey;

    
    return 0;
}