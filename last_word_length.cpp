#include <iostream>
#include <string>
using namespace std;

int lengthOfLastWord(string s) {
    int len = 0;
    int i = s.size() - 1;
    
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    
    while (i >= 0 && s[i] != ' ') {
        len++;
        i--;
    }
    
    return len;
}

int main() {
    string s;
    getline(cin, s);
    cout << lengthOfLastWord(s) << endl;
    return 0;
}
