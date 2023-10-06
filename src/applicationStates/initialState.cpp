#include <iostream>
#include <string>

#include <sgc/applicationStates/initialState.h>
#include <sgc/applicationStates/createOperatorsState.h>

#include <libcryptosec/BigInteger.h>
#include <libcryptosec/Random.h>
#include <libcryptosec/ByteArray.h>

using namespace sgc;

InitialState::InitialState(Application* app) : ApplicationState(app) {}

InitialState::~InitialState() {}

// TODO: implementar checagem de sessão existente
void InitialState::run() {
    MessageDigest::loadMessageDigestAlgorithms();
    
    Application* app = this->getApp();

    app->setCertificateAuthority(CertificateAuthority::generateNew());

    std::cout << "Quantos operadores irão participar desta decisão?\n";
    int numOperators;
    std::cin >> numOperators;
    std::cin.ignore(1, '\n');

    app->setNumOperators(numOperators);
    app->changeState(new CreateOperatorsState(app));

    return;
}