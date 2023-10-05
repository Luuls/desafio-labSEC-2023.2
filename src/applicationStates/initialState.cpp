#include <iostream>

#include <sgc/applicationStates/initialState.h>
#include <sgc/applicationStates/createOperatorsState.h>

sgc::InitialState::InitialState(Application* app) : ApplicationState(app) {}

sgc::InitialState::~InitialState() {}

void sgc::InitialState::run() {
    std::cout << "hello world from initial state" << std::endl;
    this->getApp()->changeState(new CreateOperatorsState(this->getApp()));
}