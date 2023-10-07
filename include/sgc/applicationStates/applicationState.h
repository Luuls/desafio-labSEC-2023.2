#pragma once

#include <sgc/application.h>

namespace sgc {

// Classe base para implementar o padrão de projeto State
class ApplicationState {
public:
    ApplicationState(Application* app);
    virtual ~ApplicationState() {};

    virtual void run() = 0;

    Application* getApp() const;

private:
    Application* app;
};

}