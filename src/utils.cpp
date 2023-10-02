#include <cctype>

#include <sgc/utils.h>

std::string sgc::toLowerString(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {
        str[i] = std::tolower(str[i]);
    }
    return str;
}