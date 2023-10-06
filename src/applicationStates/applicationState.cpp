#include <sgc/applicationStates/applicationState.h>

using namespace sgc;

ApplicationState::ApplicationState(Application* app) : app(app) {}

Application* ApplicationState::getApp() const {
    return this->app;
}