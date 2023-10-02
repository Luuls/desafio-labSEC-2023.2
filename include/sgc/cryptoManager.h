#pragma once

#include <string>

#include <sgc/pemManipulator.h>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/PrivateKey.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {
    
class CryptoManager {
public:
    CryptoManager(const std::string& cpf);

    PrivateKey* getPrivateKey();
    // Certificate* getCertificate();
    // void sign(const std::string& content);
    

private:
    std::string hashedCpf;
    PemManipulator* pemManipulator;
};

}