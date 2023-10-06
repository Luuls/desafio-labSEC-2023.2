#include <sgc/applicationStates/verifyState.h>

#include <libcryptosec/Signer.h>

using namespace sgc;

VerifyState::VerifyState(Application* app) : ApplicationState(app) {}

VerifyState::~VerifyState() {}

void VerifyState::run() {
    Application* app = this->getApp();

    //----------- verificar os certificados com base na AC --------------------------
    std::cout << "[***] ----------------- VERIFICAÇÃO DOS CERTIFICADOS -----------------\n\n";

    std::vector<Operator> operators = app->getOperators();
    CertificateAuthority ca = app->getCertificateAuthority();
    Certificate* caCert = ca.getCertificate();
    for (size_t i = 0; i < operators.size(); i++) {
        Operator currentOp = operators[i];
        Certificate* currentOpCert = currentOp.getCertificate();
        std::vector<Certificate> untrustedChain(1, *currentOpCert);
        std::vector<Certificate> trustedChain(1, *caCert);
        CertPathValidator validator(*currentOpCert, untrustedChain, trustedChain);

        std::cout << "[*] Verificando certificado de " << currentOp.getName() << "...\n";
        bool isValid = validator.verify();
        delete currentOpCert;

        if (!isValid) {
            std::vector<CertPathValidatorResult> results = validator.getResults();
            for (size_t j = 0; j < results.size(); j++) {
                std::cout << results[i].getMessage() << "\n";
            }

            std::cout << "[!] O certificado do operador " << currentOp.getName();
            std::cout << " (" << currentOp.getId() << ") não é valido.\n";
            std::cout << "Possível fraude detectada. Encerrando execução...\n";

            delete caCert;
            app->setIsRunning(false);
            return;
        }

        std::cout << "[+] Certificado validado com sucesso.\n\n";
    }
    // -----------------------------------------------------------------------------------


    // --------- verificar autenticidade das assinaturas ---------------------------------
    std::cout << "[***] ----------------- VERIFICAÇÃO DAS ASSINATURAS -----------------\n\n";

    std::string pdfContent = app->getDocumentContent();

    MessageDigest md(MessageDigest::SHA256);
    md.init(MessageDigest::SHA256);
    ByteArray hashedPdfContent = md.doFinal(pdfContent);

    std::vector<Signature> signatures = app->getDocumentSignatures();
    for (size_t i = 0; i < signatures.size(); i++) {
        Signature currentSignature = signatures[i];
        Certificate* currentCert = currentSignature.getSigner();
        PublicKey* signerPubKey = currentCert->getPublicKey();
        ByteArray currentSignedMessage = currentSignature.getSignedMessage();
        std::string signerName = currentCert->getSubject().getEntries(RDNSequence::COMMON_NAME)[0];

        std::cout << "[*] Verificando assinatura de " << signerName << "...\n";
        bool isSignatureValid = Signer::verify(
            *signerPubKey,
            currentSignedMessage,
            hashedPdfContent,
            MessageDigest::SHA256
        );

        if (!isSignatureValid) {
            std::cout << "[!] A assinatura do operador " << signerName << " não é valida.\n";
            std::cout << "Possível fraude detectada. Encerrando execução...\n";
            app->setIsRunning(false);

            delete currentCert;
            return;
        }

        std::cout << "[+] Assinatura validada com sucesso.\n\n";

        delete signerPubKey;
        delete currentCert;
    }
    // -----------------------------------------------------------------------------------

    app->setIsRunning(false);
    return;
}