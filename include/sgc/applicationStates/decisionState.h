#pragma once

#include <string>

#include <sgc/application.h>
#include <sgc/applicationStates/applicationState.h>

namespace sgc {

// \brief Estado da aplicação que realizar a votação dos operadores
// e assina o documento ou não
class DecisionState : public ApplicationState {
public:
    DecisionState(Application* app);
    ~DecisionState();

    void run();
};

}