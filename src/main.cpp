#include <sgc/application.h>

#include <libcryptosec/RSAKeyPair.h>

int main(int argc, char** argv) {
    sgc::Application app(argc, argv);
    app.run();

    return 0;
}