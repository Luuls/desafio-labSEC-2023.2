#include <sgc/applicationStates/createOperatorsState.h>
#include <sgc/operator.h>

sgc::CreateOperatorsState::CreateOperatorsState(Application* app) : ApplicationState(app) {}

sgc::CreateOperatorsState::~CreateOperatorsState() {}

void sgc::CreateOperatorsState::run() {
    sgc::Application* app = this->getApp();
    
    for (size_t i = 0; i < app->getNumOperators(); i++) {
        std::cout << "Operador número " << i + 1 << ", insira seus dados\n";
        std::cout << "Nome: ";
        std::string name;
        getline(cin, name);

        std::cout << "CPF (somente números): ";
        std::string cpf;
        std::cin >> cpf;

        std::cout << "E-mail: ";
        std::string email;
        std::cin >> email;
        std::cin.ignore(1, '\n');

        sgc::Operator op(name, cpf, email);
        operators.push_back(op);
    }
    this->getApp()->setIsRunning(false);
}