#include <sgc/applicationStates/createOperatorsState.h>
#include <sgc/operator.h>
#include <sgc/operatorBuilder.h>

using namespace sgc;

CreateOperatorsState::CreateOperatorsState(Application* app) : ApplicationState(app) {}

CreateOperatorsState::~CreateOperatorsState() {}

void CreateOperatorsState::run() {
    Application* app = this->getApp();

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

        Operator op = OperatorBuilder::generateNew(
            name,
            cpf,
            email,
            app->getCa()
        );

        app->addOperator(op);
    }

    app->setIsRunning(false);
    return;
}