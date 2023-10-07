#pragma once

#include <vector>
#include <string>

#include <sgc/operator.h>
#include <sgc/certificateAuthority.h>
#include <sgc/document.h>

namespace sgc {

// forward declaration
class ApplicationState;

// classe que gerencia e mantém os dados da aplicação
class Application {
public:
    Application(int argc, char** argv);
    ~Application();

    // \brief executa a aplicação com base no estado atual;
    void run();
    void setIsRunning(bool isRunning);

    // \brief setter para o state. Troca o estado atual da aplicação
    // \param newState ponteiro para o novo estado da aplicação
    void changeState(ApplicationState* newState);

    // \return quantidade de parâmetros passados na linha de comando
    int getArgc() const;
    // \return vetor de strings com os parâmetros passados na linha de comando
    char** getArgv() const;

    Document getDocument();
    // \brief adiciona uma nova assinatura ao documento interno
    // \param signature assinatura a ser adicionada
    void addSignature(const Signature& signature);
    std::string getDocumentContent();
    std::vector<Signature> getDocumentSignatures();

    size_t getNumOperators() const;
    void setNumOperators(size_t numOperators);

    // getter para os operadores
    std::vector<Operator> getOperators();
    // \brief adiciona um operador ao vetor de operadores da aplicação
    // \param op operador a ser adicionado
    void addOperator(Operator& op);

    CertificateAuthority getCertificateAuthority();
    void setCertificateAuthority(const CertificateAuthority& ca);

private:
    bool isRunning;

    int argc;
    char** argv;

    // documento a ser assinado
    Document document;
    // quantidade operadores envolvidos na decisão
    size_t numOperators;
    // operadores que foram cadastrados na execução do programa
    std::vector<sgc::Operator> operators;
    CertificateAuthority ca;

    ApplicationState* state;
};

}