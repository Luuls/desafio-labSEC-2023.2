#pragma once

#include <sgc/applicationStates/applicationState.h>

namespace sgc {

// \brief Estado da aplicação que cria os operadores
class CreateOperatorsState : public ApplicationState {
public:
    CreateOperatorsState(Application* app);
    ~CreateOperatorsState();
    void run();
};

}