#pragma once

#include <string>

#include <sgc/pemManipulator.h>
#include <sgc/operator.h>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/PrivateKey.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

class CryptoManager {
public:

    CryptoManager();
    CryptoManager(const std::string& id);
    CryptoManager(const sgc::Operator& op);

    ~CryptoManager();

public:
    void setOperator(const sgc::Operator& op);
    void setOpId(const std::string& id);
    
    PrivateKey* getOpPrivateKey();
    
    Certificate getOpCertificate();
    Certificate getCaCertificate();
    // void sign(const std::string& content);

    std::string getHashedCaId() const {
        return this->hashedCaId;
    }

    ByteArray sign(std::string& message);
    bool verify(std::string& message, ByteArray& signature);

    // para uso interno da classe
private:
    void generateKeyPairAndCertificate(const sgc::Operator& op);

private:
    std::string hashedOpId;
    std::string opKeyPath;
    std::string opCertPath;

    std::string hashedCaId;

    PemManipulator* pemManipulator;
};

}