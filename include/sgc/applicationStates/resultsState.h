#pragma once

#include <sgc/applicationStates/applicationState.h>

namespace sgc {

class ResultsState : public ApplicationState {
public:
    ResultsState(Application* app);
    ~ResultsState();

    void run();
};

}