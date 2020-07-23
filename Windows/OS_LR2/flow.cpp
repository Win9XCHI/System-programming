#include "flow.h"

flow::flow() {
    hHANDLE = nullptr;
}

flow::flow(int num, LPTHREAD_START_ROUTINE name) : type(name), Number(num) {}

flow::~flow() {
    Close();
}

bool flow::ThrStart() {
    ResumeThread(hHANDLE);
    return true;
}

bool flow::ThrSUSPENDED() {
    SuspendThread(hHANDLE);
    return true;
}

bool flow::CreateT() {
    hHANDLE = CreateThread(NULL, 0, type, (PVOID)Number, CREATE_SUSPENDED, NULL);
    //cout << endl << hHANDLE;
    return true;
}

bool flow::WFSO(DWORD time, HANDLE hSemaphore) {
    if (hSemaphore != nullptr) {
        WaitForSingleObject(hSemaphore, time);
    } else {
        WaitForSingleObject(hHANDLE, time);
    }
}

void flow::Close() {
    CloseHandle(hHANDLE);
}
