#ifndef CRITSEC_H
#define CRITSEC_H
#include <windows.h>

class CritSec {
    CRITICAL_SECTION section;
public:
    CritSec();
    ~CritSec();

    bool CreateCritSec();
    bool DeleteCritSec();

    void Entrance();
    void Exit();
};

#endif // CRITSEC_H
