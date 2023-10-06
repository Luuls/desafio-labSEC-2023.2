#include <sgc/applicationStates/decisionState.h>

using namespace sgc;

DecisionState::DecisionState(Application* app) : ApplicationState(app) {}

DecisionState::~DecisionState() {}

void DecisionState::run() {
    Application* app = this->getApp();

}