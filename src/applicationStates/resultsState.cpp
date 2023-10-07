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
    // Se o número de assinaturas for diferente do número de operadores,
    // significa que algum operador não assinou. Portanto, não foi possível
    // firmar um acordo entre eles.

    //
    int votedNo = app->getNumOperators() - signatures.size();
    if (app->getNumOperators() != signatures.size()) {
        std::cout << "Não foi possível firmar um acordo entre os operadores.\n";
        std::cout << "A UsiNUFSC permancerá ativa.\n\n";
        std::cout << votedNo << " operador" << (votedNo == 1 ? "" : "es");
        std::cout << " não " << (votedNo == 1 ? "assinou" : "assinaram") << " o documento.\n";
        app->setIsRunning(false);
        return;
    }

    // se não, todos assinaram.
    std::cout << "A UsiNUFSC será desligada. A votação foi unânime.\n\n";

    std::cout << "--------------- ASSINATURAS ---------------\n\n";
    // Mostra no terminal as assinaturas e os certificados dos operadores
    for (size_t i = 0; i < signatures.size(); i++) {
        Signature signature = signatures[i];
        Certificate* cert = signature.getSigner();
        Operator op(OperatorBuilder::fromCertificate(*cert));

        std::cout << op;
        std::cout << "Assinatura: " << toLowerString(signature.getSignedMessage().toHex()) << "\n";

        std::cout << "----------------------------------------------\n\n";

        delete cert;
    }

    // Imprime o hash do conteúdo do documento
    std::string pdfContent = app->getDocumentContent();
    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    std::string hashedPdfContent = toLowerString(md.doFinal(pdfContent).toHex());

    std::cout << "Resumo criptográfico do documento em SHA256:\n" << hashedPdfContent << '\n';
    
    app->setIsRunning(false);
    return;
}