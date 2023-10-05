#include <sgc/application.h>
#include <sgc/applicationStates/initialState.h>

sgc::Application::Application(int argc, char* argv[]) {
    this->state = new InitialState(this);
}

sgc::Application::~Application() {
    if (this->state != NULL) {
        delete this->state;
    }
}

void sgc::Application::run() {
    while (this->isRunning) {
        this->state->run();
    }
}

void sgc::Application::setIsRunning(bool isRunning) {
    this->isRunning = isRunning;
}

void sgc::Application::changeState(ApplicationState* newState) {
    if (this->state != NULL) {
        delete this->state;
    }

    this->state = newState;
}