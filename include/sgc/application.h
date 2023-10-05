#pragma once

#include <vector>
#include <string>

#include <sgc/operator.h>

namespace sgc {

class ApplicationState;

class Application {
public:
    Application(int argc, char* argv[]);
    ~Application();

    void run();
    void setIsRunning(bool isRunning);

    void changeState(ApplicationState* newState);

private:
    ApplicationState* state;
    bool isRunning;

    std::vector<sgc::Operator> operators;
};

}