#pragma once
#include "List.h"
#include "Event.h"
#include <string>
using namespace std;

const int cmAvg = 10;

class Dialog : public List {
protected:
    int EndState;

public:
    Dialog();
    virtual ~Dialog();

    virtual void GetEvent(TEvent& event);
    virtual int Execute();
    virtual void HandleEvent(TEvent& event);
    virtual void ClearEvent(TEvent& event);
    int Valid();
    void EndExec();
};
