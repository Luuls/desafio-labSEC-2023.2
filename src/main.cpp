#include <iostream>

#include "include/operator.h"

int main() {
    sgc::Operator op1("Luan", "8289129821", "luansmoraes13@gmail.com");

    std::cout << op1.getName() << '\n';
    op1.setName("Luan2");
    std::cout << op1.getName() << '\n';

    return 0;
}