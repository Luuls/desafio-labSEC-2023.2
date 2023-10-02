#include <string>

#include <sgc/cryptoManager.h>
#include <sgc/utils.h>

#include <libcryptosec/MessageDigest.h>

sgc::CryptoManager::CryptoManager(const std::string& cpf) : pemManipulator(NULL) {
    std::string cpfCopy = cpf;
    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    this->hashedCpf = sgc::toLowerString(md.doFinal(cpfCopy).toHex());
}

// @brief Retorna a chave privada presente em ./data/keys/<cpf hash>.pem.
// Mas ela retorna um objeto alocado. Portanto, não se esqueça de deletá-lo
// @return Ponteiro para a chave privada recém alocada
PrivateKey* sgc::CryptoManager::getPrivateKey() {
    this->pemManipulator = new PemManipulator("./data/keys/" + this->hashedCpf + ".pem");

    std::string pemPrivateKey = this->pemManipulator->getFileContent();
    delete this->pemManipulator;
    this->pemManipulator = NULL;

    PrivateKey* privateKey = new PrivateKey(pemPrivateKey);
    return privateKey;
}