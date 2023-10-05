#include <iostream>

#include <sgc/operator.h>

sgc::Operator::Operator(
    const std::string& name,
    const std::string& id,
    const std::string& email
) : name(name), id(id), email(email) {}

std::string sgc::Operator::getName() const { return name; }
void sgc::Operator::setName(const std::string& newName) { name = newName; }

std::string sgc::Operator::getId() const { return id; }
void sgc::Operator::setId(const std::string& newId) { id = newId; }

std::string sgc::Operator::getEmail() const { return email; }
void sgc::Operator::setEmail(const std::string& newEmail) { email = newEmail; }

//@brief Print operator's data
void sgc::Operator::printData() const{
    std::cout << "Nome: " << name << '\n';
    std::cout << "CPF: " << id << '\n';
    std::cout << "E-mail: " << email << '\n';
}