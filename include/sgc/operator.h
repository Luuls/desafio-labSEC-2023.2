#pragma once

#include <string>

namespace sgc {

class Operator {
public:
    Operator(
        const std::string& name,
        const std::string& cpf,
        const std::string& email
    );

    std::string getName() const;
    void setName(const std::string& newName);

    std::string getCpf() const;
    void setCpf(const std::string& newCpf);

    std::string getEmail() const;
    void setEmail(const std::string& newEmail);

    void printData() const;

private:
    std::string name;
    std::string cpf;
    std::string email;
};

}