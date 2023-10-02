#pragma once

#include <string>

#include <libcryptosec/RSAKeyPair.h>

class KeyManager {
public:
    KeyManager();

    // TODO: implementar construtor para receber caminhos para as chaves
    // KeyManager(const std::string& publicKeyPath, const std::string& privateKeyPath);

private:
    RSAKeyPair keyPair;
};