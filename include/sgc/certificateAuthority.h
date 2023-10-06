#pragma once

#include <string>

#include <libcryptosec/RSAKeyPair.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

class CertificateAuthority {
public:
    CertificateAuthority();
    CertificateAuthority(const CertificateAuthority& ca);
    ~CertificateAuthority();
    
    static CertificateAuthority fromFiles();
    static CertificateAuthority generateNew();

    // atribuição por cópia
    CertificateAuthority& operator=(const CertificateAuthority& ca);

    PrivateKey* getPrivateKey() const;
    PublicKey* getPublicKey() const;
    Certificate* getCertificate() const;

private:
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