#include <iostream>

#include <sgc/operator.h>

#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/RSAKeyPair.h>

using namespace sgc;

Operator::Operator(const Operator& op) {
    this->name = op.name;
    this->id = op.id;
    this->email = op.email;
    this->privateKey = NULL;
    this->publicKey = NULL;
    this->certificate = NULL;

    if (op.publicKey != NULL) {
        std::string pem = op.publicKey->getPemEncoded();
        this->publicKey = new RSAPublicKey(pem);
    }

    if (op.privateKey != NULL) {
        std::string pem = op.privateKey->getPemEncoded();
        this->privateKey = new RSAPrivateKey(pem);
    }

    if (op.certificate != NULL) {
        this->certificate = new Certificate(*op.certificate);
    }
}

Operator::Operator(
    const std::string& name,
    const std::string& id,
    const std::string& email,
    PublicKey* publicKey,
    PrivateKey* privateKey,
    Certificate* certificate
) : name(name), id(id), email(email), publicKey(publicKey), privateKey(privateKey), certificate(certificate) {}

Operator::~Operator() {
    delete this->publicKey;
    delete this->privateKey;
    delete this->certificate;
}

std::string Operator::getName() const { return name; }

std::string Operator::getId() const { return id; }

std::string Operator::getEmail() const { return email; }

PublicKey* Operator::getPublicKey() const {
    std::string pem = this->publicKey->getPemEncoded();
    return new RSAPublicKey(pem);
}

PrivateKey* Operator::getPrivateKey() const {
    std::string pem = this->privateKey->getPemEncoded();
    return new RSAPrivateKey(pem);
}

Certificate* Operator::getCertificate() const {
    return new Certificate(*this->certificate);
}

//@brief Print operator's data
void Operator::printData() const {
    std::cout << "Nome: " << name << '\n';
    std::cout << "CPF: " << id << '\n';
    std::cout << "E-mail: " << email << '\n';
}