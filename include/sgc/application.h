#pragma once

#include <vector>
#include <string>

#include <sgc/operator.h>
#include <sgc/certificateAuthority.h>

namespace sgc {

class ApplicationState;

class Application {
public:
    Application(int argc, char** argv);
    ~Application();

    void run();
    void setIsRunning(bool isRunning);

    void changeState(ApplicationState* newState);

    int getArgc() const;
    char** getArgv() const;

    size_t getNumOperators() const;
    void setNumOperators(size_t numOperators);

    std::vector<Operator> getOperators();
    void addOperator(Operator& op);

    CertificateAuthority getCa();
    void setCa(const CertificateAuthority& ca);

private:
    bool isRunning;

    int argc;
    char** argv;

    // quantidade operadores envolvidos na decisão
    size_t numOperators;
    // operadores que foram cadastrados na execução do programa
    // (não necessariamente a mesma quantidade que numOperators)
    std::vector<sgc::Operator> operators;
    CertificateAuthority ca;

    ApplicationState* state;
};

}