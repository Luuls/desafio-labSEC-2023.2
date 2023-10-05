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
    sgc::Application* app = this->getApp();
    // int argc = app->getArgc();
    // char** argv = app->getArgv();

    MessageDigest::loadMessageDigestAlgorithms();

    std::cout << "Quantos operadores irão participar desta decisão?\n";
    int numOperators;
    std::cin >> numOperators;
    std::cin.ignore(1, '\n');

    app->setNumOperators(numOperators);
    app->changeState(new CreateOperatorsState(this->getApp()));
}