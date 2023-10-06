#pragma once

#include <string>

#include <libcryptosec/ByteArray.h>
#include <libcryptosec/certificate/Certificate.h>

namespace sgc {

class Signature {
public:
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