#pragma once

#include <string>

#include <sgc/application.h>
#include <sgc/applicationStates/applicationState.h>

namespace sgc {

class DecisionState : public ApplicationState {
public:
    DecisionState(Application* app);
    ~DecisionState();

    void run();

};

}