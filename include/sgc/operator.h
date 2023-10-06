#pragma once

#include <string>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

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

    Operator(const Operator& op);

    ~Operator();

    std::string getName() const;
    std::string getId() const;
    std::string getEmail() const;

    PublicKey* getPublicKey() const;
    PrivateKey* getPrivateKey() const;

    Certificate* getCertificate() const;

    void printData() const;

private:
    std::string name;
    std::string id;
    std::string email;

    PublicKey* publicKey;
    PrivateKey* privateKey;
    Certificate* certificate;
};

}