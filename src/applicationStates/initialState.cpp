#include <iostream>
#include <string>

#include <sgc/applicationStates/initialState.h>
#include <sgc/applicationStates/createOperatorsState.h>

#include <libcryptosec/BigInteger.h>
#include <libcryptosec/Random.h>
#include <libcryptosec/ByteArray.h>

sgc::InitialState::InitialState(Application* app) : ApplicationState(app) {}

sgc::InitialState::~InitialState() {}

// TODO: implementar checagem de sessão existente
void sgc::InitialState::run() {
    MessageDigest::loadMessageDigestAlgorithms();
    
    sgc::Application* app = this->getApp();

    app->setCa(CertificateAuthority::generateNew());
    CertificateAuthority ca(app->getCa());
    Certificate* caCert = ca.getCertificate();
    std::cout << caCert->getXmlEncoded() << '\n';
    delete caCert;

    std::cout << "Quantos operadores irão participar desta decisão?\n";
    int numOperators;
    std::cin >> numOperators;
    std::cin.ignore(1, '\n');

    app->setNumOperators(numOperators);
    app->changeState(new CreateOperatorsState(this->getApp()));

    return;
}