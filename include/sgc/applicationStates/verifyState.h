#pragma once

#include <sgc/applicationStates/applicationState.h>

namespace sgc {

// \brief Estado da aplicação que realiza a verificação dos certificados e assinaturas
class VerifyState : public ApplicationState {
public:
    VerifyState(Application* app);
    ~VerifyState();

    void run();
};

}