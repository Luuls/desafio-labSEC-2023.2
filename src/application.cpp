#include <sgc/application.h>
#include <sgc/applicationStates/initialState.h>

sgc::Application::Application(int argc, char** argv)
    : argc(argc), argv(argv), numOperators(0), operators() {
        
    this->state = new InitialState(this);

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
}

sgc::Application::~Application() {
    if (this->state != NULL) {
        delete this->state;
    }
}

void sgc::Application::run() {
    while (this->isRunning) {
        this->state->run();
    }
}

void sgc::Application::setIsRunning(bool isRunning) {
    this->isRunning = isRunning;
}

void sgc::Application::changeState(ApplicationState* newState) {
    if (this->state != NULL) {
        delete this->state;
    }

    this->state = newState;
}

int sgc::Application::getArgc() const {
    return this->argc;
}

char** sgc::Application::getArgv() const {
    return this->argv;
}

size_t sgc::Application::getNumOperators() const {
    return this->numOperators;
}

void sgc::Application::setNumOperators(size_t numOperators) {
    this->numOperators = numOperators;
}

std::vector<sgc::Operator&>& sgc::Application::getOperators() {
    return this->operators;
}

void sgc::Application::addOperator(Operator& op) {
    this->operators.push_back(op);
}