#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

const int MAX = 256;


bool isOnlyDigits(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i])) return false;
    }
    return true;
}


void toIdentifier(char word[]) {
    if (!isalpha(word[0]) && word[0] != '_') {
        int len = strlen(word);
        for (int i = len; i >= 0; i--) {
            word[i + 1] = word[i];
        }
        word[0] = '_';
    }
    

    for (int i = 0; word[i] != '\0'; i++) {
        if (!isalnum(word[i]) && word[i] != '_') {
            word[i] = '_';
        }
    }
}

int main() {
    char str[MAX];
    
    cout << "Введите строку (до 255 символов, заканчивается точкой):" << endl;
    cin.getline(str, MAX);
    
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '.') {
        str[len - 1] = '\0';
    }
    
    char words[50][MAX]; 
    int wordCount = 0;
    
    char* token = strtok(str, " ");
    while (token != NULL) {
        strcpy(words[wordCount], token);
        wordCount++;
        token = strtok(NULL, " ");
    }
    
    char result[MAX] = "";
    
    for (int i = 0; i < wordCount; i++) {
        if (isOnlyDigits(words[i])) {
            continue;
        }
        
        toIdentifier(words[i]);
        
        if (strlen(result) > 0) {
            strcat(result, " ");
        }
        strcat(result, words[i]);
    }
    
    cout << "\nПреобразованная строка:" << endl;
    cout << result << endl;
    
    return 0;
}