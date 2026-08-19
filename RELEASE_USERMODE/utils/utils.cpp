#include "utils.h"

int utils::generateRandomInteger(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

std::string utils::generateRandomString(size_t length) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::random_device rd;  // Seed for randomness
    std::mt19937 generator(rd());  // Mersenne Twister random number generator
    std::uniform_int_distribution<size_t> distribution(0, charset.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += charset[distribution(generator)];
    }

    return randomString;
}
