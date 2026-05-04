#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int countWords(char s[]) {
    int count = 0;
    bool inWord = false;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ' && s[i] != '\n') {
            if (!inWord) {
                count++;
                inWord = true;
            }
        } else {
            inWord = false;
        }
    }
    return count;
}

void findLongestWord(char s[], char longest[]) {
    char word[100];
    int maxLen = 0;
    int i = 0;
    while (s[i] != '\0') {
        while (s[i] == ' ') i++;
        int j = 0;
        while (s[i] != ' ' && s[i] != '\0' && s[i] != '\n') {
            word[j++] = s[i++];
        }
        word[j] = '\0';
        if (j > maxLen) {
            maxLen = j;
            strcpy(longest, word);
        }
    }
}

int main() {
    ofstream f1("F1.txt");
    if (!f1) {
        cout << "Ошибка создания файла F1!" << endl;
        return 1;
    }
    cout << "Введите 10 строк:" << endl;
    cin.ignore();
    for (int i = 0; i < 10; i++) {
        char s[256];
        cin.getline(s, 256);
        f1 << s << endl;
    }
    f1.close();
    cout << "Файл F1 создан!" << endl;
    
    ifstream fin("F1.txt");
    ofstream fout("F2.txt");
    if (!fin || !fout) {
        cout << "Ошибка открытия файлов!" << endl;
        return 1;
    }
    char line[256];
    cout << "\nСтроки с одним словом (скопированы в F2):" << endl;
    cout << "=============================" << endl;
    while (fin.getline(line, 256)) {
        if (countWords(line) == 1) {
            fout << line << endl;
            cout << line << endl;
        }
    }
    fin.close();
    fout.close();
    cout << "=============================" << endl;
    cout << "Файл F2 создан!" << endl;
    
    ifstream fin2("F2.txt");
    if (!fin2) {
        cout << "Файл F2 пуст или не существует!" << endl;
        return 1;
    }
    char longestWord[100] = "";
    char curLine[256];
    while (fin2.getline(curLine, 256)) {
        char word[100];
        findLongestWord(curLine, word);
        if (strlen(word) > strlen(longestWord)) {
            strcpy(longestWord, word);
        }
    }
    fin2.close();
    if (strlen(longestWord) > 0) {
        cout << "\nСамое длинное слово в файле F2: " << longestWord << endl;
        cout << "Длина: " << strlen(longestWord) << " символов" << endl;
    } else {
        cout << "\nВ файле F2 нет слов!" << endl;
    }
    return 0;
}