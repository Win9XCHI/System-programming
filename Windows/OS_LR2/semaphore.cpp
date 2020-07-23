#include "semaphore.h"

Semaphore::Semaphore() {

}

Semaphore::Semaphore(LPSECURITY_ATTRIBUTES atr1, LONG atr2, LONG atr3, LPCTSTR atr4) {
    lpSemaphoreAttributes = atr1;	// атрибут доступа
    lInitialCount = atr2;		// инициализированное начальное состояние счетчика
    lMaximumCount = atr3;			// максимальное количество обращений
    lpName = atr4;
}

Semaphore::~Semaphore() {
    Close();
}

bool Semaphore::CreateSem() {
    hSemaphore = CreateSemaphore(lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName);
}

bool Semaphore::AddCountSem(LONG atr1, LPLONG atr2) {
    ReleaseSemaphore(hSemaphore, atr1, atr2);
}

void Semaphore::Close() {
    CloseHandle(hSemaphore);
}

HANDLE Semaphore::GetSemaphore() {
    return hSemaphore;
}
