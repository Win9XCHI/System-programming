#include "event.h"

Event::Event() {
    hEvent = nullptr;
}

Event::Event(PSECURITY_ATTRIBUTES a, BOOL b, BOOL c, PCTSTR d) : psa(a), fManualReset(b), fInitialState(c), pszName(d), hEvent(nullptr) {

}

Event::~Event() {
    Close();
}

void Event::Close() {
    CloseHandle(hEvent);
    std::cout << std::endl << "Event: Close handle";
}

bool Event::CreateE() {
    hEvent = CreateEvent(psa, fManualReset, fInitialState, pszName);
    return hEvent != nullptr;
}

BOOL Event::Set() {
    return SetEvent(hEvent);
}

BOOL Event::Reset() {
    return ResetEvent(hEvent);
}

BOOL Event::Pulse() {
    return PulseEvent(hEvent);
}

HANDLE Event::GetEvent() {
    return hEvent;
}

bool Event::Open(DWORD a, BOOL b) {
    hEvent = OpenEvent(a, b, pszName);
    return hEvent != nullptr;
}
