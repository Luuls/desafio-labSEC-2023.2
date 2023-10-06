#include <sgc/application.h>
#include <sgc/applicationStates/initialState.h>

using namespace sgc;

Application::Application(int argc, char** argv)
    : argc(argc), argv(argv), numOperators(0), operators(), state(NULL) {
    
    std::string usage = "Uso: " + std::string(argv[0]) + " <caminho do PDF>";
    if (argc < 2) {
        std::cerr << usage << '\n';
        this->setIsRunning(false);
        return;
    }

    else if (argc > 2) {
        std::cerr << "Erro: muitos argumentos." << '\n';
        std::cerr << usage << '\n';
        this->setIsRunning(false);
        return;
    }

    this->document = Document(argv[1]);
    this->changeState(new InitialState(this));
}

Application::~Application() {
    if (this->state != NULL) {
        delete this->state;
    }
}

void Application::run() {
    while (this->isRunning) {
        this->state->run();
    }
}

void Application::setIsRunning(bool isRunning) {
    this->isRunning = isRunning;
}

void Application::changeState(ApplicationState* newState) {
    if (this->state != NULL) {
        delete this->state;
    }

    this->state = newState;
}

int Application::getArgc() const {
    return this->argc;
}

char** Application::getArgv() const {
    return this->argv;
}

Document Application::getDocument() {
    return this->document;
}

void Application::addSignature(const Signature& signature) {
    this->document.addSignature(signature);
}

std::string Application::getDocumentContent() {
    return this->document.getContent();
}

std::vector<Signature> Application::getDocumentSignatures() {
    return this->document.getSignatures();
}

size_t Application::getNumOperators() const {
    return this->numOperators;
}

void Application::setNumOperators(size_t numOperators) {
    this->numOperators = numOperators;
}

std::vector<Operator> Application::getOperators() {
    return this->operators;
}

void Application::addOperator(Operator& op) {
    this->operators.push_back(op);
}

CertificateAuthority Application::getCertificateAuthority() {
    return this->ca;
}

void Application::setCertificateAuthority(const CertificateAuthority& ca) {
    this->ca = ca;
}