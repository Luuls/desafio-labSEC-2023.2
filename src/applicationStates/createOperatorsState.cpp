#include <sgc/applicationStates/createOperatorsState.h>

sgc::CreateOperatorsState::CreateOperatorsState(Application* app) : ApplicationState(app) {}

sgc::CreateOperatorsState::~CreateOperatorsState() {}

void sgc::CreateOperatorsState::run() {
    std::cout << "hello from create operators state" << std::endl;
    this->getApp()->setIsRunning(false);
}