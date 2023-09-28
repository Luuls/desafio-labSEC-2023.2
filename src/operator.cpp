#include "include/operator.h"

sgc::Operator::Operator(
    const std::string& name,
    const std::string& cpf,
    const std::string& email
) : name(name), cpf(cpf), email(email) {}

std::string sgc::Operator::getName() const { return name; }
void sgc::Operator::setName(const std::string& newName) { name = newName; }

std::string sgc::Operator::getCpf() const { return cpf; }
void sgc::Operator::setCpf(const std::string& newCpf) { cpf = newCpf; }

std::string sgc::Operator::getEmail() const { return email; }
void sgc::Operator::setEmail(const std::string& newEmail) { email = newEmail; }