#pragma once

#include <string>
#include <vector>

#include <sgc/signature.h>

#include <libcryptosec/Pkcs7SignedData.h>
#include <libcryptosec/Pkcs7SignedDataBuilder.h>

namespace sgc {

// \brief Classe que representa um documento. Possui assinaturas e conteúdo em string
class Document {
public:
    Document(const std::string& content);
    Document();

    void addSignature(const Signature& signature);

    std::vector<Signature> getSignatures() const;
    std::string getContent() const;

private:
    std::vector<Signature> signatures;
    std::string content;
};

}