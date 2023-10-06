#include <sgc/applicationStates/decisionState.h>
#include <sgc/applicationStates/verifyState.h>
#include <sgc/PDFReader.h>
#include <sgc/document.h>
#include <sgc/utils.h>

#include <libcryptosec/Pkcs7SignedDataBuilder.h>
#include <libcryptosec/Pkcs7SignedData.h>
#include <libcryptosec/Signer.h>

using namespace sgc;

DecisionState::DecisionState(Application* app) : ApplicationState(app) {}

DecisionState::~DecisionState() {}

struct Answer {
    Operator& op;
    bool answer;
};

void DecisionState::run() {
    Application* app = this->getApp();

    std::string pdfContent = app->getDocumentContent();

    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    ByteArray hashedPdfContent = md.doFinal(pdfContent);

    std::vector<Operator> operators = app->getOperators();
    std::vector<Answer> answers;
    size_t yesVotes = 0;

    std::cout << "\n\nAgora, os operadores deverão votar pelo desligamento ou não da Usina Nuclear da UFSC (UsiNUFSC).\n";
    for (size_t i = 0; i < operators.size(); i++) {
        Operator currentOp = operators[i];
        std::cout << currentOp.getName() << " (" << currentOp.getId() << "): ";
        std::cout << "Você é a favor de desligar a UsiNUFSC? (s/n)\n";
        char answer;
        while (true) {
            std::cin >> answer;
            if (answer != 's' && answer != 'n') {
                std::cout << "Resposta inválida. Digite 's' para SIM ou 'n' para NÃO.\n";
                continue;
            }
            break;
        }

        Answer a = { currentOp, (answer == 's') };
        answers.push_back(a);
        std::string message = "Você votou ";
        if (answer == 's') {
            yesVotes++;
            message += "SIM.";
            Certificate* currentOpCert = currentOp.getCertificate();
            PrivateKey* currentOpPrivKey = currentOp.getPrivateKey();

            ByteArray signedMessage = Signer::sign(
                *currentOpPrivKey,
                hashedPdfContent,
                MessageDigest::SHA256
            );

            Signature signature(signedMessage, currentOpCert);
            app->addSignature(signature);

            delete currentOpPrivKey;
        }
        else {
            message += "NÃO.";
        }

        std::cout << message << "\n\n";
    }

    app->changeState(new VerifyState(app));
    return;
}