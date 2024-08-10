#include "pw-gen.hpp"
#include <iostream>
#include <random>


using namespace std;

int main() {
    // TODO force minimum password to be 6 characters
    for (int i = 0; i < 10; i++) {
        cout << generate_password(16) << endl;
        // cout << randInt(0, 20) << endl;
    }

    // make warning for ambiguous characters
}