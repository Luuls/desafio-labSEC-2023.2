#pragma once

#include <sgc/applicationStates/applicationState.h>

namespace sgc {

// \brief Estado da aplicação que mostra os resultados da votação
class ResultsState : public ApplicationState {
public:
    ResultsState(Application* app);
    ~ResultsState();

    void run();
};

}