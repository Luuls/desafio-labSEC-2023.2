#pragma once

#include <string>
#include <vector>
#include <libcryptosec/RSAKeyPair.h>

namespace sgc {

// hash map simples pois c++98 não possui unordered_map
class HashMap {
public:
    HashMap(size_t buckets);

    void put(const std::string& key, const RSAKeyPair value);
    RSAKeyPair& get(const std::string& key);

    size_t getSize();

private:
    size_t hash(const std::string& key);

    std::vector<std::vector<std::pair<std::string, RSAKeyPair > > > buckets;
    size_t size;
};

} // namespace sgc