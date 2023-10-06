#include <sgc/operator.h>
#include <sgc/operatorBuilder.h>
#include <sgc/applicationStates/resultsState.h>
#include <sgc/utils.h>

using namespace sgc;

ResultsState::ResultsState(Application* app) : ApplicationState(app) {}

ResultsState::~ResultsState() {};

void ResultsState::run() {
    Application* app = this->getApp();

    std::cout << "--------------- RESULTADO DA VOTAÇÃO ---------------\n\n";

    std::vector<Signature> signatures = app->getDocumentSignatures();
    std::vector<Operator> operators = app->getOperators();
    if (app->getNumOperators() != signatures.size()) {
        std::cout << "Não foi possível firmar um acordo entre os operadores.\n";
        std::cout << operators.size() - signatures.size() << " operadores não assinaram o documento.\n";
        app->setIsRunning(false);
        return;
    }

    std::cout << "A UsiNUFSC será desligada. A votação foi unânime.\n\n";

    std::cout << "--------------- ASSINATURAS ---------------\n\n";
    for (size_t i = 0; i < signatures.size(); i++) {
        Signature signature = signatures[i];
        Certificate* cert = signature.getSigner();
        Operator op(OperatorBuilder::fromCertificate(*cert));
        std::cout << op;
        std::cout << "Assinatura: " << toLowerString(signature.getSignedMessage().toHex()) << "\n";

        std::cout << "----------------------------------------------\n\n";

        delete cert;
    }

    std::string pdfContent = app->getDocumentContent();
    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    std::string hashedPdfContent = toLowerString(md.doFinal(pdfContent).toHex());
    std::cout << "Resumo criptográfico do documento em SHA256:\n" << hashedPdfContent << '\n';
    app->setIsRunning(false);
    return;
}