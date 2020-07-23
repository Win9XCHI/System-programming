#ifndef FLOW_H
#define FLOW_H
#include <windows.h>

DWORD WINAPI Reader(PVOID pvParam);
DWORD WINAPI Writer(PVOID pvParam);

class flow {
    HANDLE hHANDLE;
    LPTHREAD_START_ROUTINE type;
    int Number;

    public:
        flow();
        flow(int, LPTHREAD_START_ROUTINE);
        ~flow();
        bool CreateT();
        bool ThrStart();
        bool ThrSUSPENDED();
        bool WFSO(DWORD, HANDLE);
        void Close();
};

#endif // FLOW_H
