#include <sgc/signature.h>

using namespace sgc;

Signature::Signature(ByteArray signedMessage, Certificate* signer) :
    signedMessage(signedMessage), signer(signer) {}

Signature::Signature(const Signature& signature) {
    this->signedMessage = signature.signedMessage;
    this->signer = new Certificate(*signature.signer);
}

Signature::~Signature() {
    delete this->signer;
}

ByteArray Signature::getSignedMessage() const {
    return this->signedMessage;
}

Certificate* Signature::getSigner() const {
    return new Certificate(*this->signer);
}