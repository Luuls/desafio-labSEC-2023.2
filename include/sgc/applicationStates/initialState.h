#pragma once

#include <vector>

#include <sgc/applicationStates/applicationState.h>
#include <sgc/application.h>

namespace sgc {

class InitialState : public ApplicationState {
public:
    InitialState(Application* app);
    ~InitialState();
    void run();
};

}