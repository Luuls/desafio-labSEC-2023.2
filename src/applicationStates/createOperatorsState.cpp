#include <sgc/applicationStates/createOperatorsState.h>
#include <sgc/operator.h>
#include <sgc/operatorBuilder.h>

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

        Operator op = OperatorBuilder::generateNew(
            name,
            cpf,
            email,
            app->getCa()
        );

        app->addOperator(op);
    }

    std::vector<Operator> operators = app->getOperators();
    for (size_t i = 0; i < operators.size(); i++) {
        Certificate* currentOpCert = operators[i].getCertificate();
        std::cout << currentOpCert->getXmlEncoded() << '\n';
        delete currentOpCert;
    }

    app->setIsRunning(false);
    return;
}