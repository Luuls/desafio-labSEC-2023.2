#include <iostream>

#include "operator.h"
#include <libcryptosec/certificate/Certificate.h>
#include <libcryptosec/RSAKeyPair.h>

int main() {
    sgc::Operator op1("Luan", "8289129821", "luansmoraes13@gmail.com");

    std::cout << op1.getName() << '\n';
    op1.setName("Luan2");
    std::cout << op1.getName() << '\n';

    RSAKeyPair rsa(2048);
    std::cout << rsa.getPublicKey() << '\n';


    return 0;
}