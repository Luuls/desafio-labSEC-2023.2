#include <sgc/applicationStates/applicationState.h>

sgc::ApplicationState::ApplicationState(Application* app) : app(app) {}

sgc::Application* sgc::ApplicationState::getApp() const {
    return this->app;
}