#include "mutex.h"

Mutex::Mutex() {
    hMutex = nullptr;
}

Mutex::Mutex(PSECURITY_ATTRIBUTES atr1, BOOL atr2, PCTSTR atr3) {
    psa = atr1;
    fInitialOwner = atr2;
    pszName = atr3;
    hMutex = nullptr;
}

Mutex::~Mutex() {
    Close();
}

bool Mutex::CreateM() {
    hMutex = CreateMutex(psa, fInitialOwner, pszName);
    return hMutex != nullptr;
}

bool Mutex::AddCountMut() {
    ReleaseMutex(hMutex);
}

void Mutex::Close() {
    CloseHandle(hMutex);
    std::cout << std::endl << "Close handle";
}

HANDLE Mutex::GetMutex() {
    return hMutex;
}

bool Mutex::Open(DWORD atr1, BOOL atr2, LPCTSTR atr3) {
    hMutex = OpenMutex(atr1, atr2, atr3);
    return hMutex != nullptr;
}
