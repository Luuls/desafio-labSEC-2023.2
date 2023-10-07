#pragma once

#include <string>

#include <libcryptosec/ByteArray.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

// \brief Classe para guardar informações de uma assinatura
class Signature {
public:
    // \param signedMessage Mensagem já assinada
    // \param signer Certificado do assinante
    Signature(ByteArray signedMessage, Certificate* signer);
    Signature(const Signature& signature);
    ~Signature();

    ByteArray getSignedMessage() const;
    Certificate* getSigner() const;

private:
    ByteArray signedMessage;
    Certificate* signer;
};

}