#include <sgc/applicationStates/decisionState.h>
#include <poppler/cpp/poppler-document.h>
using namespace sgc;

DecisionState::DecisionState(Application* app) : ApplicationState(app) {}

DecisionState::~DecisionState() {}

struct Answer {
    Operator& op;
    bool answer;
};

void DecisionState::run() {
    Application* app = this->getApp();

    std::cout << "\n\nAgora, os operadores deverao votar pelo desligamento ou nao da Usina Nuclear da UFSC (UsiNUFSC).\n";

    std::vector<Operator> operators = app->getOperators();
    std::vector<Answer> answers;
    size_t yesVotes = 0;
    for (size_t i = 0; i < operators.size(); i++) {
        Operator currentOp = operators[i];
        std::cout << currentOp.getName() << " (" << currentOp.getId() << "): ";
        std::cout << "Deseja desligar a UsiNUFSC? (s/n)\n";
        char answer;
        std::cin >> answer;

        Answer a = { currentOp, (answer == 's') };
        answers.push_back(a);

        std::string message = "Voce votou ";
        if (answer == 's') {
            yesVotes++;
            message += "sim";
        }
        else {
            message += "nao";
        }

        std::cout << message << "\n\n";
        
        // precisa de uma classe para representar o documento
        // document.addSignature(signature);

        // TODO: implementar o resto da leitura das decisões
    }

}