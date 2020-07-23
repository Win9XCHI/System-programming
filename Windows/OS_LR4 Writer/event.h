#ifndef EVENT_H
#define EVENT_H
#include <windows.h>
#include <iostream>

class Event {

    HANDLE hEvent;
    PSECURITY_ATTRIBUTES psa;
    BOOL fManualReset;
    BOOL fInitialState;
    PCTSTR pszName;

public:
    Event();
    Event(PSECURITY_ATTRIBUTES, BOOL, BOOL, PCTSTR);
    ~Event();

    bool CreateE();
    BOOL Set();
    BOOL Reset();
    BOOL Pulse();
    HANDLE GetEvent();
    void Close();
    bool Open(DWORD, BOOL);
};

#endif // EVENT_H
