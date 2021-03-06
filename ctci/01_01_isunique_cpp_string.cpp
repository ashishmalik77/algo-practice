#include <iostream>

using namespace std;
bool isunique(string str) {
    bool temp[256];

    for (int i=0; i<256; i++) {
        temp[i] = false;
    }
    int i=0;
    while(str.length() >= i) {
        if (temp[str[i]]) {
            return false;
        }
        temp[str[i]] = true;
        i++;
    }

    return true;
}

int main() {
    cout << isunique("devendra") <<endl;
    cout << isunique("dev") << endl;
    return 0;
}