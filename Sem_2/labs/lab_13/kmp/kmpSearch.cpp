#include <iostream>
#include <string>

using namespace std;

int kmpSearch(const string& text, const string& pattern) {
    int textLen = text.size();
    int patternLen = pattern.size();

    if (textLen == 0 || patternLen == 0 || patternLen > textLen) {
        return -1;
    }

    int* pref = new int[patternLen];
    pref[0] = 0;
    for (int i = 1, j = 0; i < patternLen; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pref[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        pref[i] = j;
    }
    for (int i = 0, j = 0; i < textLen; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pref[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == patternLen) {
            delete[] pref;
            return i - patternLen + 1;
        }
    }

    delete[] pref;
    return -1;
}

int main() {
    string text = "idechvetothamam turckayabanya";
    string pattern = "etothamam";
    int index = kmpSearch(text, pattern);
    if (index != -1) {
        cout << index << endl;
    } else {
        cout << "Not found" << endl;
    }

    return 0;
}