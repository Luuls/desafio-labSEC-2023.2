#pragma once

#include <string>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

// \brief Classe que representa a autoridade certificadora
class CertificateAuthority {
public:
    CertificateAuthority();
    CertificateAuthority(const CertificateAuthority& ca);
    ~CertificateAuthority();

    // \brief Gera uma nova autoridade certificadora
    static CertificateAuthority generateNew();

    // atribuição por cópia
    CertificateAuthority& operator=(const CertificateAuthority& ca);

    PrivateKey* getPrivateKey() const;
    PublicKey* getPublicKey() const;
    Certificate* getCertificate() const;

private:
    // \brief Construtor privado que recebe os dados da autoridade certificadora
    // para que somente a função generateNew possa criar uma nova autoridade
    CertificateAuthority(
        PrivateKey* privateKey,
        PublicKey* publicKey,
        Certificate* certificate
    );

    PrivateKey* privateKey;
    PublicKey* publicKey;
    Certificate* certificate;
};

}