#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <windows.h>

class Semaphore {
    HANDLE hSemaphore;
    LPSECURITY_ATTRIBUTES lpSemaphoreAttributes;	// атрибут доступа
    LONG lInitialCount;		// инициализированное начальное состояние счетчика
    LONG lMaximumCount;			// максимальное количество обращений
    LPCTSTR lpName;
public:
    Semaphore();
    Semaphore(LPSECURITY_ATTRIBUTES, LONG, LONG, LPCTSTR);
    ~Semaphore();

    bool CreateSem();
    bool AddCountSem(LONG, LPLONG);
    void Close();
    HANDLE GetSemaphore();
};

#endif // SEMAPHORE_H
