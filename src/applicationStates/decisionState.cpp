#include <sgc/applicationStates/decisionState.h>
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

    PDFReader pdfReader(app->getArgv()[1]);
    std::string pdfContent = pdfReader.getFileContent();
    Document document(pdfContent);

    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    ByteArray hashedPdfContent = md.doFinal(pdfContent);

    std::vector<Operator> operators = app->getOperators();
    std::vector<Answer> answers;
    size_t yesVotes = 0;

    std::cout << "\n\nAgora, os operadores deverao votar pelo desligamento ou nao da Usina Nuclear da UFSC (UsiNUFSC).\n";
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
            message += "SIM.";
            Certificate* currentOpCert = currentOp.getCertificate();
            PrivateKey* currentOpPrivKey = currentOp.getPrivateKey();

            ByteArray signedMessage = Signer::sign(
                *currentOpPrivKey,
                hashedPdfContent,
                MessageDigest::SHA256
            );

            Signature signature(signedMessage, currentOpCert);
            document.addSignature(signature);

            delete currentOpPrivKey;
        }
        else {
            message += "NAO.";
        }

        std::cout << message << "\n\n";

        // TODO: implementar o resto da leitura das decisões
    }

    if (yesVotes == 0) {
        std::cout << "Nenhum operador votou pelo desligamento da UsiNUFSC. A usina continuara ativa.\n";
        app->setIsRunning(false);
        return;
    }

    // verificar as assinaturas

    std::vector<Signature> signatures = document.getSignatures();
    document.getContent();
    for (size_t i = 0; i < signatures.size(); i++) {
        Signature currentSignature = signatures[i];
        Certificate* currentCert = currentSignature.getSigner();
        PublicKey* signerPubKey = currentCert->getPublicKey();
        ByteArray currentSignedMessage = currentSignature.getSignedMessage();
        std::string signerName = currentCert->getSubject().getEntries(RDNSequence::COMMON_NAME)[0];
        std::cout << "Verificando assinatura de " << signerName << "...\n";
        bool isSignatureValid = Signer::verify(
            *signerPubKey,
            currentSignedMessage,
            hashedPdfContent,
            MessageDigest::SHA256
        );

        if (!isSignatureValid) {
            std::cout << "A assinatura do operador " << signerName << " nao e valida.\n";
            app->setIsRunning(false);

            delete currentCert;
            return;
        }

        std::cout << "Assinatura verificada com sucesso\n";

        delete signerPubKey;
        delete currentCert;
    }

    app->setIsRunning(false);
    return;
}