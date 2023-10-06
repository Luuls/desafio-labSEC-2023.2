#include <sgc/certificateAuthority.h>
#include <sgc/pemManipulator.h>
#include <sgc/utils.h>
#include <sgc/constants.h>

#include <libcryptosec/certificate/CertificateBuilder.h>

sgc::CertificateAuthority::CertificateAuthority()
    : privateKey(NULL), publicKey(NULL), certificate(NULL) {}

sgc::CertificateAuthority::CertificateAuthority(const CertificateAuthority& ca) {
    std::string pem = ca.privateKey->getPemEncoded();
    this->privateKey = new RSAPrivateKey(pem);

    pem = ca.publicKey->getPemEncoded();
    this->publicKey = new RSAPublicKey(pem);
    
    this->certificate = new Certificate(*ca.certificate);
}

sgc::CertificateAuthority::CertificateAuthority(
    PrivateKey* privateKey,
    PublicKey* publicKey,
    Certificate* certificate
) : privateKey(privateKey), publicKey(publicKey), certificate(certificate) {}

sgc::CertificateAuthority::~CertificateAuthority() {
    if (this->privateKey != NULL) {
        delete this->privateKey;
    }

    if (this->publicKey != NULL) {
        delete this->publicKey;
    }

    if (this->certificate != NULL) {
        delete this->certificate;
    }
}

sgc::CertificateAuthority& sgc::CertificateAuthority::operator=(const CertificateAuthority& ca) {
    if (this != &ca) {
        delete this->privateKey;
        delete this->publicKey;
        delete this->certificate;

        std::string pem = ca.privateKey->getPemEncoded();
        this->privateKey = new RSAPrivateKey(pem);

        pem = ca.publicKey->getPemEncoded();
        this->publicKey = new RSAPublicKey(pem);
        this->certificate = new Certificate(*ca.certificate);
    }

    return *this;
}

sgc::CertificateAuthority sgc::CertificateAuthority::fromFiles() {}

sgc::CertificateAuthority sgc::CertificateAuthority::generateNew() {
    std::string caId = "83.899.526/0001-82";
    // CA certificate
    RDNSequence subject;
    subject.addEntry(RDNSequence::COMMON_NAME, "UFSC");
    subject.addEntry(RDNSequence::ORGANIZATION, "Universidade Federal de Santa Catarina");
    subject.addEntry(RDNSequence::ORGANIZATION_UNIT, "SeTIC");
    subject.addEntry(RDNSequence::EMAIL, "setic@contato.ufsc.br");
    // CNPJ
    // não tem um entry para id, então irei colocar no serial number
    subject.addEntry(RDNSequence::SERIAL_NUMBER, caId);
    subject.addEntry(RDNSequence::COUNTRY, "BR");
    subject.addEntry(RDNSequence::STATE_OR_PROVINCE, "SC");

    RSAKeyPair caKeyPair(2048);
    PublicKey* caPublicKey = caKeyPair.getPublicKey();
    PrivateKey* caPrivateKey = caKeyPair.getPrivateKey();

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

    Certificate* caCert = caCertBuilder.sign(*caPrivateKey, MessageDigest::SHA256);

    std::string pemCaCert = caCert->getPemEncoded();
    std::string pemCaPrivKey = caPrivateKey->getPemEncoded();

    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    std::string hashedId = sgc::toLowerString(md.doFinal(caId).toHex());

    std::string caPrivKeyPath = sgc::keysDir + hashedId + ".pem";
    std::string caCertPath = sgc::certificatesDir + hashedId + ".pem";

    PemManipulator pemManip(caPrivKeyPath);
    pemManip.writeToFile(pemCaPrivKey);
    pemManip.setOutputFilePath(caCertPath);
    pemManip.writeToFile(pemCaCert);

    return CertificateAuthority(caPrivateKey, caPublicKey, caCert);
}

PrivateKey* sgc::CertificateAuthority::getPrivateKey() const {
    std::string pem = this->privateKey->getPemEncoded();
    return new RSAPrivateKey(pem);
}

PublicKey* sgc::CertificateAuthority::getPublicKey() const {
    std::string pem = this->publicKey->getPemEncoded();
    return new RSAPublicKey(pem);
}

Certificate* sgc::CertificateAuthority::getCertificate() const {
    return new Certificate(*(this->certificate));
}