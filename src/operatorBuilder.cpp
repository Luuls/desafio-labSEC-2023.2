#include <sgc/operatorBuilder.h>
#include <sgc/pemManipulator.h>
#include <sgc/constants.h>
#include <sgc/utils.h>

#include <libcryptosec/certificate/CertificateBuilder.h>
#include <libcryptosec/certificate/Certificate.h>

sgc::Operator sgc::OperatorBuilder::fromFiles(
    const std::string& privKeyPath,
    const std::string& certPath
) {
    // TODO

    return Operator("", "", "", NULL, NULL, NULL);
}

sgc::Operator sgc::OperatorBuilder::generateNew(
    const std::string& name,
    const std::string& id,
    const std::string& email,
    const CertificateAuthority& ca
) {
    RDNSequence subject;
    subject.addEntry(RDNSequence::COMMON_NAME, name);
    subject.addEntry(RDNSequence::ORGANIZATION, "Universidade Federal de Santa Catarina");
    subject.addEntry(RDNSequence::ORGANIZATION_UNIT, "INE");
    subject.addEntry(RDNSequence::EMAIL, email);
    // CPF
    subject.addEntry(RDNSequence::SERIAL_NUMBER, id);
    subject.addEntry(RDNSequence::COUNTRY, "BR");
    subject.addEntry(RDNSequence::STATE_OR_PROVINCE, "SC");

    RSAKeyPair keyPair(2048);
    PublicKey* const publicKey = keyPair.getPublicKey();
    PrivateKey* const privateKey = keyPair.getPrivateKey();

    KeyUsageExtension keyUsage;
    keyUsage.setUsage(KeyUsageExtension::DIGITAL_SIGNATURE, true);

    // período de duração do presente desafio
    DateTime notBefore("20230927000000Z");
    DateTime notAfter("20231006000000Z");

    CertificateRequest certRequest;
    certRequest.setSubject(subject);
    certRequest.setPublicKey(*publicKey);
    certRequest.addExtension(keyUsage);
    certRequest.sign(*privateKey, MessageDigest::SHA256);

    Certificate* caCert = ca.getCertificate();
    RDNSequence caSubject = caCert->getSubject();
    PrivateKey* caPrivKey = ca.getPrivateKey();

    CertificateBuilder certBuilder(certRequest);
    certBuilder.setIssuer(caSubject);
    certBuilder.setNotBefore(notBefore);
    certBuilder.setNotAfter(notAfter);

    Certificate* const cert = certBuilder.sign(*caPrivKey, MessageDigest::SHA256);

    std::string pemCert = cert->getPemEncoded();
    std::string pemPrivKey = privateKey->getPemEncoded();

    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    std::string idCopy = id;
    std::string hashedId = sgc::toLowerString(md.doFinal(idCopy).toHex());
    std::string keyPath = sgc::keysDir + hashedId + ".pem";
    std::string certPath = sgc::certificatesDir + hashedId + ".pem";

    PemManipulator pemManip(keyPath);
    pemManip.writeToFile(pemPrivKey);
    pemManip.setOutputFilePath(certPath);
    pemManip.writeToFile(pemCert);

    delete caCert;
    delete caPrivKey;

    Operator op(
        name,
        id,
        email,
        publicKey,
        privateKey,
        cert
    );

    return op;
}