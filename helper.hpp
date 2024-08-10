#ifndef HELPER_HPP
#define HELPER_HPP

#include <random>
#include <vector>
using namespace std;

// generates random inclusive integer
int randInt(int min, int max) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(min,max);
    return distribution(rng);
}

bool isVowel(char c) {
    return tolower(c) == 'a' || tolower(c) == 'e' || tolower(c) == 'i' || tolower(c) == 'o' || tolower(c) == 'u';
}

char randVowel() {
    const vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    return vowels[randInt(0,vowels.size()-1)];
}

char randConsonant() {
    const vector<char> consonants = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    return consonants[randInt(0,consonants.size()-1)];
}

#endif