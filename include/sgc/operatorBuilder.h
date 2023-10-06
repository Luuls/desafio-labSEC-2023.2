#pragma once

#include <sgc/operator.h>
#include <sgc/certificateAuthority.h>

namespace sgc {

class OperatorBuilder {
public:
    // constroi um operador a partir de um arquivo de chave privada e um de certificado
    static Operator fromCertificate(Certificate& cert);

    // constroi um operador a partir do nome, id e email e gera
    // um par de chaves e um certificado novos.
    static Operator generateNew(
        const std::string& name,
        const std::string& id,
        const std::string& email,
        const CertificateAuthority& ca
    );
};

}