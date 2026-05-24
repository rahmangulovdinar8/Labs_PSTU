#include "Dialog.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Dialog::Dialog() : Vector() {
    EndState = 0;
}

Dialog::~Dialog() {}

void Dialog::GetEvent(TEvent& event) {
    string opInt = "+-?/qms";
    string s;
    char code;
    cout << "\n> ";
    cin >> s;
    code = s[0];
    
    if (opInt.find(code) >= 0) {
        event.what = evMessage;
        switch (code) {
            case 'm': event.command = cmMake; break;
            case '+': event.command = cmAdd; break;
            case '-': event.command = cmDel; break;
            case '?': event.command = cmShow; break;
            case 'q': event.command = cmQuit; break;
            default: event.what = evNothing; break;
        }
    } else {
        event.what = evNothing;
    }
}

void Dialog::ClearEvent(TEvent& event) {
    event.what = evNothing;
}

int Dialog::Valid() {
    return EndState == 1;
}

void Dialog::EndExec() {
    EndState = 1;
}

int Dialog::Execute() {
    TEvent event;
    do {
        EndState = 0;
        GetEvent(event);
        HandleEvent(event);
    } while (!Valid());
    return EndState;
}

void Dialog::HandleEvent(TEvent& event) {
    if (event.what == evMessage) {
        switch (event.command) {
            case cmMake:
                cout << "Введите размер группы: ";
                cin >> size;
                beg = new Object*[size];
                cur = 0;
                ClearEvent(event);
                break;
            case cmAdd:
                Add();
                ClearEvent(event);
                break;
            case cmDel:
                Del();
                ClearEvent(event);
                break;
            case cmShow:
                Show();
                ClearEvent(event);
                break;
            case cmQuit:
                EndExec();
                ClearEvent(event);
                break;
            default:
                Vector::HandleEvent(event);
                break;
        }
    }
}