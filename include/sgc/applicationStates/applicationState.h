#pragma once

#include <sgc/application.h>

namespace sgc {

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