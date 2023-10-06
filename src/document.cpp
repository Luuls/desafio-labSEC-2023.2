#include <vector>

#include <sgc/document.h>

using namespace sgc;

Document::Document(const std::string& content) : content(content) {}

Document::Document() {}

void Document::addSignature(const Signature& signature) {
    this->signatures.push_back(signature);
}

std::vector<Signature> Document::getSignatures() const {
    return this->signatures;
}

std::string Document::getContent() const {
    return this->content;
}