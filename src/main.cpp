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
#include <sgc/utils.h>

#include <libcryptosec/certificate/CertificateRequest.h>
#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/certificate/CertPathValidator.h>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/MessageDigest.h>

struct Answer {
    sgc::Operator op;
    bool answer;
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
    std::string pdfContent;
    try {
        sgc::PDFReader pdfReader(pdfFilePath);
        pdfContent = pdfReader.getFileContent();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    std::vector<Answer> answers;
    std::vector<ByteArray> signatures;
    int yesVotes = 0;
    std::cout << "\n\nAgora, os operadores deverao votar para o desligamento ou nao da Usina Nuclear da UFSC (UsiNUFSC)\n\n";
    for (size_t i = 0; i < operators.size(); i++) {
        sgc::Operator currentOp = operators[i];
        manager.setOpId(currentOp.getId());
        
        std::cout << currentOp.getName() << " (" << currentOp.getId() << ')';
        std::cout << ", voce eh a favor desligar a UsiNUFSC? (s / n)\n";
        char answer;
        std::cin >> answer;
        std::cin.ignore(1, '\n');

        Answer a = { currentOp, (answer == 's') };
        answers.push_back(a);

        std::string message = "Voce votou ";
        if (answer == 's') {
            yesVotes++;
            message += "sim";
        }
        else {
            message += "nao";
        }

        std::cout << message << '\n';

        signatures.push_back(manager.sign(pdfContent));
        // armazenar e verificar assinaturas
    }

    if (yesVotes != numOperators) {
        std::cout << "A decisao nao foi unanime. Ja que nao foi possivel chegar a um acordo, a UsiNUFSC continuara funcionando.\n";
        std::cout << "De " << numOperators << " operadores, " << yesVotes << " votaram a favor do desligamento.\n";
    }

    else {
        std::cout << "A decisao foi unanime. A UsiNUFSC sera desligada.\n";
        std::cout << "De " << numOperators << " operadores, " << yesVotes << " votaram a favor do desligamento.\n";
    }

    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    md.update(pdfContent);
    std::string hashedPdfContent = sgc::toLowerString(md.doFinal().toHex());
    for (size_t i = 0; i < answers.size(); i++) {
        sgc::Operator currentOp = answers[i].op;
        manager.setOpId(currentOp.getId());
        bool verified = manager.verify(pdfContent, signatures[i]);
        if (!verified) {
            std::cout << "A assinatura de " << currentOp.getName() << " nao foi verificada.\n";
            std::cout << "Possivel fraude ocorrida. O programa sera encerrado e a decisao nao sera computada.\n";
            break;
        }
        answers[i].op.printData();
        std::cout << "Voto: " << (answers[i].answer ? "sim" : "nao") << '\n';
        std::cout << "Assinatura: " << sgc::toLowerString(signatures[i].toHex()) << '\n';
        std::cout << '\n';
    }

    std::cout << "\nResumo do PDF em SHA256: " << hashedPdfContent << '\n';

    // sgc::Operator luan(
    //     "Luan Moraes",
    //     "13397819997",
    //     "luansmoraes13@gmail.com"
    // );

    // for (int i = 0; i < operators.size(); i++) {
    //     std::string opId = operators[i].getId();
    //     manager.setOpId(opId);
    //     Certificate opCert = manager.getOpCertificate();
    //     Certificate caCert = manager.getCaCertificate();

    //     std::vector<Certificate> untrustedChain(1, opCert);
    //     std::vector<Certificate> trustedChain(1, caCert);
    //     CertPathValidator validator(opCert, untrustedChain, trustedChain);
    //     std::cout << validator.verify() << '\n';
    // }

    return 0;
}