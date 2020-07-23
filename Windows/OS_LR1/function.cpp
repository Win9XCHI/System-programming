#include "function.h"

int flow::count = 0;

DWORD WINAPI ThreadFunc(PVOID pvParam) {
    sharedResource* c = (sharedResource*) pvParam;
    //while(!c->terminated) {

        //EnterCriticalSection(&section);
        cout << c->one << endl;
        cout << "H" << endl;
        //LeaveCriticalSection(&section);
        Sleep(1000);
    //}
    cout << "Terminated: " << c->two << endl;
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType) {
    cout << "A" << endl;
    if (dwCtrlType == CTRL_C_EVENT) {
         cout << "A" << endl;
        Sleep(1000);
    }
    return true;
}
