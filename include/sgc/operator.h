#pragma once

#include <string>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

class Operator {
public:
    // Operator(
    //     const std::string& name,
    //     const std::string& id,
    //     const std::string& email
    // );

    Operator(
        const std::string& name,
        const std::string& id,
        const std::string& email,
        const RSAKeyPair& keyPair,
        Certificate* certificate
    );

    ~Operator();

    std::string getName() const;
    void setName(const std::string& newName);

    std::string getId() const;
    void setId(const std::string& newId);

    std::string getEmail() const;
    void setEmail(const std::string& newEmail);

    void printData() const;

private:
    std::string name;
    std::string id;
    std::string email;

    RSAKeyPair keyPair;
    Certificate* certificate;
};

}