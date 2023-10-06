#pragma once

#include <sgc/applicationStates/applicationState.h>

namespace sgc {

class VerifyState : public ApplicationState {
public:
    VerifyState(Application* app);
    ~VerifyState();

    void run();
};

}