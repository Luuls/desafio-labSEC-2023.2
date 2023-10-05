#pragma once

#include <sgc/applicationStates/applicationState.h>

namespace sgc {

class CreateOperatorsState : public ApplicationState {
public:
    CreateOperatorsState(Application* app);
    ~CreateOperatorsState();
    void run();
};

}