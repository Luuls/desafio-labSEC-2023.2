#include <string>

#include <sgc/cryptoManager.h>
#include <sgc/pemManipulator.h>
#include <sgc/utils.h>

#include <libcryptosec/MessageDigest.h>
#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/certificate/CertificateRequest.h>
#include <libcryptosec/certificate/CertificateBuilder.h>
#include <libcryptosec/certificate/CertPathValidator.h>

sgc::CryptoManager::CryptoManager() {
    MessageDigest md(MessageDigest::SHA256);

    md.init(MessageDigest::SHA256);
    std::string caId = "83.899.526/0001-82";
    const std::string HashedCaId = sgc::toLowerString(md.doFinal(caId).toHex());
    this->hashedCaId = HashedCaId;
    const std::string caKeyPath = "./data/keys/" + HashedCaId + ".pem";
    const std::string caCertPath = "./data/certificates/" + HashedCaId + ".pem";
    this->pemManipulator = new PemManipulator(caKeyPath);
    try {
        this->pemManipulator->getFileContent();
    }
    catch (const std::runtime_error& e) {
        // CA certificate
        RDNSequence subject;
        subject.addEntry(RDNSequence::COMMON_NAME, "UFSC");
        subject.addEntry(RDNSequence::ORGANIZATION, "Universidade Federal de Santa Catarina");
        subject.addEntry(RDNSequence::ORGANIZATION_UNIT, "SeTIC");
        subject.addEntry(RDNSequence::EMAIL, "setic@contato.ufsc.br");
        // CNPJ
        subject.addEntry(RDNSequence::UNKNOWN, caId);
        subject.addEntry(RDNSequence::COUNTRY, "BR");
        subject.addEntry(RDNSequence::STATE_OR_PROVINCE, "SC");

        RSAKeyPair caKeyPair(2048);
        PublicKey* const caPublicKey = caKeyPair.getPublicKey();
        PrivateKey* const caPrivateKey = caKeyPair.getPrivateKey();

        KeyUsageExtension keyUsage;
        keyUsage.setUsage(KeyUsageExtension::KEY_CERT_SIGN, true);
        keyUsage.setUsage(KeyUsageExtension::DIGITAL_SIGNATURE, true);

        // período de duração do presente desafio
        DateTime notBefore("20230927000000Z");
        DateTime notAfter("20231006000000Z");

        CertificateBuilder caCertBuilder;
        caCertBuilder.setSubject(subject);
        caCertBuilder.setPublicKey(*caPublicKey);
        caCertBuilder.setIssuer(subject);
        caCertBuilder.setNotBefore(notBefore);
        caCertBuilder.setNotAfter(notAfter);
        caCertBuilder.addExtension(keyUsage);

        Certificate* const caCert = caCertBuilder.sign(*caPrivateKey, MessageDigest::SHA256);

        std::string pemCaCert = caCert->getPemEncoded();
        std::string pemCaPrivKey = caPrivateKey->getPemEncoded();

        this->pemManipulator->writeToFile(pemCaPrivKey);
        this->pemManipulator->setOutputFilePath(caCertPath);
        this->pemManipulator->writeToFile(pemCaCert);

        delete caPublicKey;
        delete caPrivateKey;
        delete caCert;
    }
}

sgc::CryptoManager::CryptoManager(const sgc::Operator& op) {
    std::string opId = op.getId();
    MessageDigest md(MessageDigest::SHA256);

    md.init(MessageDigest::SHA256);
    std::string caId = "83.899.526/0001-82";
    const std::string HashedCaId = sgc::toLowerString(md.doFinal(caId).toHex());
    this->hashedCaId = HashedCaId;
    const std::string caKeyPath = "./data/keys/" + HashedCaId + ".pem";
    const std::string caCertPath = "./data/certificates/" + HashedCaId + ".pem";
    this->pemManipulator = new PemManipulator(caKeyPath);
    try {
        this->pemManipulator->getFileContent();
    }
    catch (const std::runtime_error& e) {
        // CA certificate
        RDNSequence subject;
        subject.addEntry(RDNSequence::COMMON_NAME, "UFSC");
        subject.addEntry(RDNSequence::ORGANIZATION, "Universidade Federal de Santa Catarina");
        subject.addEntry(RDNSequence::ORGANIZATION_UNIT, "SeTIC");
        subject.addEntry(RDNSequence::EMAIL, "setic@contato.ufsc.br");
        // CNPJ
        subject.addEntry(RDNSequence::UNKNOWN, caId);
        subject.addEntry(RDNSequence::COUNTRY, "BR");
        subject.addEntry(RDNSequence::STATE_OR_PROVINCE, "SC");

        RSAKeyPair caKeyPair(2048);
        PublicKey* const caPublicKey = caKeyPair.getPublicKey();
        PrivateKey* const caPrivateKey = caKeyPair.getPrivateKey();

        KeyUsageExtension keyUsage;
        keyUsage.setUsage(KeyUsageExtension::KEY_CERT_SIGN, true);
        keyUsage.setUsage(KeyUsageExtension::DIGITAL_SIGNATURE, true);

        // período de duração do presente desafio
        DateTime notBefore("20230927000000Z");
        DateTime notAfter("20231006000000Z");

        CertificateBuilder caCertBuilder;
        caCertBuilder.setSubject(subject);
        caCertBuilder.setPublicKey(*caPublicKey);
        caCertBuilder.setIssuer(subject);
        caCertBuilder.setNotBefore(notBefore);
        caCertBuilder.setNotAfter(notAfter);
        caCertBuilder.addExtension(keyUsage);

        Certificate* const caCert = caCertBuilder.sign(*caPrivateKey, MessageDigest::SHA256);

        std::string pemCaCert = caCert->getPemEncoded();
        std::string pemCaPrivKey = caPrivateKey->getPemEncoded();

        this->pemManipulator->writeToFile(pemCaPrivKey);
        this->pemManipulator->setOutputFilePath(caCertPath);
        this->pemManipulator->writeToFile(pemCaCert);

        delete caPublicKey;
        delete caPrivateKey;
        delete caCert;
    }

    md.init(MessageDigest::SHA256);
    this->hashedOpId = sgc::toLowerString(md.doFinal(opId).toHex());
    this->opKeyPath = "./data/keys/" + this->hashedOpId + ".pem";
    this->opCertPath = "./data/certificates/" + this->hashedOpId + ".pem";

    this->pemManipulator->setInputFilePath(this->opKeyPath);
    try {
        this->pemManipulator->getFileContent();
    }
    catch (const std::runtime_error& e) {
        this->generateKeyPairAndCertificate(op);
    }
}

// TODO: implementar construtor que recebed id de operador e id de CA e verifica se
// já existe um certificado para a CA. Se não existir, gera um novo certificado.
// Também verifica se já existe um certificado para o operador. Se não existir, gera um novo.
sgc::CryptoManager::CryptoManager(const std::string& id) {
    std::string idCopy = id;
    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    this->hashedOpId = sgc::toLowerString(md.doFinal(idCopy).toHex());
    this->opKeyPath = "./data/keys/" + this->hashedOpId + ".pem";
    this->opCertPath = "./data/certificates/" + this->hashedOpId + ".pem";

    std::string caId = "83.899.526/0001-82";
    md.init(MessageDigest::SHA256);
    this->hashedCaId = sgc::toLowerString(md.doFinal(caId).toHex());

    if (this->hashedOpId == this->hashedCaId) {
        throw std::logic_error("O id do operador não pode ser igual ao id da CA.");
    }

    this->pemManipulator = new PemManipulator(this->opKeyPath);
}

sgc::CryptoManager::~CryptoManager() {
    delete this->pemManipulator;
}

void sgc::CryptoManager::setOperator(const sgc::Operator& op) {
    std::string idCopy = op.getId();
    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    this->hashedOpId = sgc::toLowerString(md.doFinal(idCopy).toHex());
    this->opKeyPath = "./data/keys/" + this->hashedOpId + ".pem";
    this->opCertPath = "./data/certificates/" + this->hashedOpId + ".pem";

    this->pemManipulator->setInputFilePath(this->opKeyPath);
    try {
        this->pemManipulator->getFileContent();
    }
    catch (const std::runtime_error& e) {
        this->generateKeyPairAndCertificate(op);
    }
}

void sgc::CryptoManager::setOpId(const std::string& id) {
    std::string idCopy = id;
    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    this->hashedOpId = sgc::toLowerString(md.doFinal(idCopy).toHex());
    this->opKeyPath = "./data/keys/" + this->hashedOpId + ".pem";
    this->opCertPath = "./data/certificates/" + this->hashedOpId + ".pem";

    this->pemManipulator->setInputFilePath(this->opKeyPath);
    try {
        this->pemManipulator->getFileContent();
    }
    catch (const std::runtime_error& e) {
        throw std::runtime_error("Não existe um certificado para o operador com id " + id);
    }
}

void sgc::CryptoManager::generateKeyPairAndCertificate(const sgc::Operator& op) {
    RDNSequence subject;
    subject.addEntry(RDNSequence::COMMON_NAME, op.getName());
    subject.addEntry(RDNSequence::ORGANIZATION, "Universidade Federal de Santa Catarina");
    subject.addEntry(RDNSequence::ORGANIZATION_UNIT, "INE");
    subject.addEntry(RDNSequence::EMAIL, op.getEmail());
    // CPF
    subject.addEntry(RDNSequence::UNKNOWN, op.getId());
    subject.addEntry(RDNSequence::COUNTRY, "BR");
    subject.addEntry(RDNSequence::STATE_OR_PROVINCE, "SC");

    RSAKeyPair opKeyPair(2048);
    PublicKey* const opPublicKey = opKeyPair.getPublicKey();
    PrivateKey* const opPrivateKey = opKeyPair.getPrivateKey();

    KeyUsageExtension keyUsage;
    keyUsage.setUsage(KeyUsageExtension::DIGITAL_SIGNATURE, true);

    // período de duração do presente desafio
    DateTime notBefore("20230927000000Z");
    DateTime notAfter("20231006000000Z");

    CertificateRequest opCertRequest;
    opCertRequest.setSubject(subject);
    opCertRequest.setPublicKey(*opPublicKey);
    opCertRequest.addExtension(keyUsage);
    opCertRequest.sign(*opPrivateKey, MessageDigest::SHA256);

    // ------------ obtendo dados da CA --------------
    this->pemManipulator->setInputFilePath("./data/certificates/" + this->hashedCaId + ".pem");
    std::string pemCaCert = pemManipulator->getFileContent();
    Certificate caCert(pemCaCert);
    RDNSequence caSubject(caCert.getSubject());

    this->pemManipulator->setInputFilePath("./data/keys/" + this->hashedCaId + ".pem");
    std::string pemCaPrivKey = pemManipulator->getFileContent();
    PrivateKey* const caPrivKey = new PrivateKey(pemCaPrivKey);
    // -----------------------------------------------
    
    CertificateBuilder opCertBuilder(opCertRequest);
    opCertBuilder.setIssuer(caSubject);
    opCertBuilder.setNotBefore(notBefore);
    opCertBuilder.setNotAfter(notAfter);

    Certificate* const opCert = opCertBuilder.sign(*caPrivKey, MessageDigest::SHA256);

    std::string pemOpCert = opCert->getPemEncoded();
    std::string pemOpPrivKey = opPrivateKey->getPemEncoded();

    this->pemManipulator->setOutputFilePath(this->opKeyPath);
    this->pemManipulator->writeToFile(pemOpPrivKey);
    this->pemManipulator->setOutputFilePath(this->opCertPath);
    this->pemManipulator->writeToFile(pemOpCert);

    delete opPublicKey;
    delete opPrivateKey;
    delete opCert;
    delete caPrivKey;
}

// @brief Retorna a chave privada presente em ./data/keys/<id hash>.pem.
// Mas ela retorna um objeto alocado. Portanto, não se esqueça de deletá-lo
// @return Ponteiro para a chave privada recém alocada
PrivateKey* sgc::CryptoManager::getPrivateKey() {
    this->pemManipulator->setInputFilePath("./data/keys/" + this->hashedOpId + ".pem");

    std::string pemPrivateKey = this->pemManipulator->getFileContent();

    PrivateKey* privateKey = new PrivateKey(pemPrivateKey);
    return privateKey;
}

Certificate sgc::CryptoManager::getOpCertificate() {
    this->pemManipulator->setInputFilePath(this->opCertPath);
    std::string pemOpCert = this->pemManipulator->getFileContent();
    return Certificate(pemOpCert);
}
Certificate sgc::CryptoManager::getCaCertificate() {
    this->pemManipulator->setInputFilePath("./data/certificates/" + this->hashedCaId + ".pem");
    std::string pemCaCert = this->pemManipulator->getFileContent();
    return Certificate(pemCaCert);
}