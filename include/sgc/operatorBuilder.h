#pragma once

#include <sgc/operator.h>
#include <sgc/certificateAuthority.h>

namespace sgc {

// \brief Classe que constroi um operador
class OperatorBuilder {
public:
    // constroi um operador a partir de um certificado
    // (lê a chave privada do arquivo ./data/keys/<hash do id>.pem)
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