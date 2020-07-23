#include "critsec.h"

CritSec::CritSec() {

}

CritSec::~CritSec() {

}

bool CritSec::CreateCritSec() {
    InitializeCriticalSection(&section);
}

bool CritSec::DeleteCritSec() {
    DeleteCriticalSection(&section);
}

void CritSec::Entrance() {
    EnterCriticalSection(&section);
}

void CritSec::Exit() {
    LeaveCriticalSection(&section);
}
