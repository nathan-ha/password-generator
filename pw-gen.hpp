#ifndef PW_GEN_HPP
#define PW_GEN_HPP

#include <iostream>
#include "helper.hpp"

using namespace std;

char get_next_letter(const string& password) {

    // first letter is capital
    if (password.empty()) {
        bool isVowel = randInt(1, 26) <= 5; // 5/26 chance of being a vowel
        char firstLetter = isVowel ? randVowel() : randConsonant();
        return toupper(firstLetter);
    }

    // 1 in 15 chance of inserting a dash
    if (randInt(1, 15) == 1 && password.back() != '-') {
        return '-';
    }

    bool lastLetterVowel = isVowel(password.back());
    if (password.back() == '-') lastLetterVowel = static_cast<bool>(randInt(0, 1));

    // 1 in 10 chance of having two consonants in a row or two vowels in a row
    if (randInt(1, 10) == 1) {
        return lastLetterVowel ? randVowel() : randConsonant();
    }

    if (!lastLetterVowel) {
        return randVowel();
    }

    char nextLetter = randConsonant();
    // An 'h' may follow a consonant, but not another 'h'.
    if (nextLetter == 'h' && password.back() != '-' && !isVowel(password.back()) && password.back() != 'h') {
        return 'h';
    } else {
        while (nextLetter == 'h') nextLetter = randConsonant();
    }
    // An 'L' may follow a consonant, unless it there is already a consonant followed by an 'l'
    if (nextLetter == 'l' && password.size() >= 3 && password.back() == 'l' && password[password.size() - 2] != '-' && !isVowel(password[password.size() - 2])) {
        return 'l';
    } else {
        while (nextLetter == 'l') nextLetter = randConsonant();
    }
    // a 'c' may be followed by a 'k' if the 'c' follows a vowel (e.g. ack).
    if (nextLetter == 'k' && password.size() >= 3 && password.back() == 'c' && isVowel(password[password.size() - 2])) {
        return 'k';
    } else {
        while (nextLetter == 'k') nextLetter = randConsonant();
    }
    return nextLetter;
}

string generate_password(int pw_length) {
    const vector<char> specials = {'!', '@', '#', '$', '%', '^', '&'};
    string password;
    for (int i = 0; i < pw_length - 3; i++) {
        password += get_next_letter(password);
    }

    // add symbol and number at end
    bool symbolFirst = randInt(0, 1);
    string twoDigits;
    twoDigits.push_back( static_cast<char>(randInt(48, 57)) );
    twoDigits.push_back( static_cast<char>(randInt(48, 57)) );

    if (symbolFirst) {
        password += specials[randInt(0, specials.size() - 1)];
        password += twoDigits;
    } else {
        password += twoDigits;
        password += specials[randInt(0, specials.size() - 1)];
    }

    return password;
}


#endif