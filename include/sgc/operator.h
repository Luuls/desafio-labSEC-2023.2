#pragma once

#include <string>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

// \brief Classe para representar os operadores
class Operator {
public:
    Operator(
        const std::string& name,
        const std::string& id,
        const std::string& email,
        PublicKey* publicKey,
        PrivateKey* privateKey,
        Certificate* certificate
    );

    // \brief Construtor de cópia
    Operator(const Operator& op);

    ~Operator();

    std::string getName() const;
    std::string getId() const;
    std::string getEmail() const;

    PublicKey* getPublicKey() const;
    PrivateKey* getPrivateKey() const;

    Certificate* getCertificate() const;

private:
    std::string name;
    std::string id;
    std::string email;

    PublicKey* publicKey;
    PrivateKey* privateKey;
    Certificate* certificate;
};

}

// \brief Sobrecarga para imprimir as informações do operador
// \param os Stream de saída
// \param op Operador a ser impresso
// \return Stream de saída para encadeamento
std::ostream& operator<<(std::ostream& os, const sgc::Operator& op);