#pragma once

#include <vector>

#include <sgc/applicationStates/applicationState.h>
#include <sgc/application.h>

namespace sgc {

// \brief Estado da aplicação que mostra a tela inicial da aplicação
class InitialState : public ApplicationState {
public:
    InitialState(Application* app);
    ~InitialState();
    void run();
};

}