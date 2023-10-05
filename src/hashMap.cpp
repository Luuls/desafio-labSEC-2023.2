#include <string>

#include <sgc/hashMap.h>

#include <libcryptosec/MessageDigest.h>

sgc::HashMap::HashMap(size_t buckets) : buckets(buckets), size(0) {}

void sgc::HashMap::put(const std::string& key, const RSAKeyPair value) {
    size_t bucketIndex = this->hash(key);

    std::vector<std::pair<std::string, RSAKeyPair > >& bucket(this->buckets[bucketIndex]);
    for (size_t i = 0; i < bucket.size(); i++) {
        if (bucket[i].first == key) {
            bucket[i].second = value;
            return;
        }
    }

    bucket.push_back(std::make_pair(key, value));
    size++;
}

RSAKeyPair& sgc::HashMap::get(const std::string& key) {
    size_t bucketIndex = this->hash(key);

    std::vector<std::pair<std::string, RSAKeyPair > >& bucket(this->buckets[bucketIndex]);
    for (size_t i = 0; i < bucket.size(); i++) {
        if (bucket[i].first == key) {
            return bucket[i].second;
        }
    }

    throw std::out_of_range("Key not found");
}

size_t sgc::HashMap::getSize() {
    return this->size;
}

size_t sgc::HashMap::hash(const std::string& key) {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash += i ^ key[i];
    }

    return hash % buckets.size();
}