#include <iostream>
#include <stdexcept>
#include <termios.h>

#include <sgc/operator.h>
#include <sgc/PDFReader.h>

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

        std::cout << "Senha: ";

        std::string password;
        struct termios oldt, newt;
        tcgetattr(0, &oldt); // Salva as configurações do terminal
        newt = oldt;
        newt.c_lflag &= ~ECHO; // Desabilita a exibição dos caracteres
        tcsetattr(0, TCSANOW, &newt); // Aplica as novas configurações do terminal

        while (1) {
            char ch = getchar();
            if (ch == '\n') // Se Enter for pressionado, encerra o loop
                break;

            if (ch == 127) { // Se Backspace for pressionado
                if (password.length() > 0) {
                    password.erase(password.length() - 1);
                }
            }

            else {
                password += ch;
            }
        }

        tcsetattr(0, TCSANOW, &oldt); // Restaura as configurações originais do terminal

        std::cout << '\n';
        std::cout << "senha digitada: " << password << '\n';

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
        std::string pdfContent = pdfReader.getPDFContent();
        std::cout << pdfContent << '\n';
    }

    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // RSAKeyPair pair(2048);
    // std::cout << pair.getPrivateKey()->getPemEncoded() << '\n';

    return 0;
}