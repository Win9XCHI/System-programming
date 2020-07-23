#ifndef MUTEX_H
#define MUTEX_H
#include <windows.h>
#include <iostream>

class Mutex {
    HANDLE hMutex;
    PSECURITY_ATTRIBUTES psa;
    BOOL fInitialOwner;
    PCTSTR pszName;

public:
    Mutex();
    Mutex(PSECURITY_ATTRIBUTES, BOOL, PCTSTR);
    ~Mutex();

    bool CreateM();
    bool AddCountMut();
    void Close();
    HANDLE GetMutex();
    bool Open(DWORD, BOOL, LPCTSTR);
};

#endif // MUTEX_H
