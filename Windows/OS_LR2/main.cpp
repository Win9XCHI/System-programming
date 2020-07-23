#include <QCoreApplication>
#include <iostream>
#include "file.h"
#include <windows.h>
#include <cstring>
#include "mutex.h"
#define ATR "WriteData"

using namespace std;

void Write(char *, int, File*, Mutex*);
void Read(char *, int, File*, Mutex*);

bool terminated = false;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    if (argc < 3) {
        cout << endl << "min 3 par. Press any key...";
        Sleep(1000);
        exit(0);
    }
    int timeSleep = atoi(argv[3]);
    File *ReadWrite = nullptr;
    cout << endl << "Work File: " << argv[1];
    cout << endl << "Role     : "  << argv[2];
    cout << endl << "Sleep    : "  << argv[3];
    Mutex OMutex(NULL, FALSE, (PCTSTR)ATR);

    if (!OMutex.Open(MUTEX_ALL_ACCESS, FALSE, (PCTSTR)ATR)) {
         if (!OMutex.CreateM()) {
             cout << endl << "Mutex false";
             exit(0);
         }
     }
     cout << endl << "HANDLE mutex: " << OMutex.GetMutex();

     if (strcmp(argv[2], "Write") == 0) {
         Write(argv[1], timeSleep, ReadWrite, &OMutex);
     }

     if (strcmp(argv[2], "Read") == 0) {
         Read(argv[1], timeSleep, ReadWrite, &OMutex);
      }

    return a.exec();
}

BOOL WINAPI consoleHandler(DWORD signal) {

    if (signal == CTRL_C_EVENT) {
        cout << "\nCtrl-C handled\n";
        terminated = true;
        Sleep(1000);
        exit(0);
    }

    return TRUE;
}

void Write(char *filename, int timeSleep, File *WriteF, Mutex *OMutex) {

    while (!terminated) {
        DWORD result;
        result = WaitForSingleObject(OMutex->GetMutex(), INFINITE);
        if (result == WAIT_OBJECT_0) {
            WriteF = new File(filename, 'o');
            WriteF->WriteFile();
            WriteF->AddEndl();
             WriteF->Close('o');
             delete WriteF;
        }
        OMutex->AddCountMut();
        if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
             cout << "\nERROR: Could not set control handler";
         }
        Sleep((DWORD)timeSleep);
    }
    OMutex->Close();
}

void Read(char *filename, int timeSleep, File *ReadF, Mutex *OMutex) {

    while (!terminated) {
        DWORD result;
        result = WaitForSingleObject(OMutex->GetMutex(), INFINITE);
        if (result == WAIT_OBJECT_0) {
            ReadF = new File(filename, 'i');
            ReadF->ReadFile(filename);
            ReadF->Close('i');
            delete ReadF;
        }
        OMutex->AddCountMut();
        if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
                        cout << "\nERROR: Could not set control handler";
         }
        Sleep((DWORD)timeSleep);
    }
    OMutex->Close();
}

/*#include <ctime>
#include "flow.h"
#include "linelistoperations.h"
#include "semaphore.h"
#include "mutex.h"

DWORD time0 = INFINITE;
Node *Object = nullptr;
NodeThread *writers = nullptr;
NodeThread *readers = nullptr;
Semaphore Wr(NULL, 1, 1, NULL);
Semaphore Re(NULL, 0, 5, NULL);
HANDLE eOnRead = CreateEvent(NULL,true,false,NULL);
Mutex M(NULL, false, NULL);

DWORD WINAPI ReaderM(PVOID pvParam) {
    readers->info->WFSO(time0, M.GetMutex());

    cout << endl << "Number thread: " << (int)pvParam;
    cout << endl << "Amount of elements - " << CountNode(Object) << endl;
    Output(Object);

    M.AddCountMut();
    Sleep(1000);
    time0 = 0;
}

DWORD WINAPI WriterM(PVOID pvParam) {
    writers->info->WFSO(time0, M.GetMutex());

    cout << endl << "Number thread: " << (int)pvParam;
    Object = AddInEnd(Object);

    M.AddCountMut();
    Sleep(1000);
    time0 = 0;
}

/*DWORD WINAPI ReaderS(PVOID pvParam) {
    //readers->info->WFSO(time0, Re.GetSemaphore());
    HANDLE h[2];
    h[0] = eOnRead;
    h[1] = Re.GetSemaphore();
    WaitForMultipleObjects(2,h,true,INFINITE);

    cout << endl << "Number thread: " << (int)pvParam;
    cout << endl << "Amount of elements - " << CountNode(Object) << endl;
    Output(Object);

    Re.AddCountSem(1, NULL);
    Sleep(1000);
    time0 = 0;
}

DWORD WINAPI WriterS(PVOID pvParam) {
    writers->info->WFSO(time0, Wr.GetSemaphore());
    ResetEvent(eOnRead);

    cout << endl << "Number thread: " << (int)pvParam;
    Object = AddInEnd(Object);

    SetEvent(eOnRead);
    Wr.AddCountSem(1, NULL);
    Sleep(1000);
    time0 = 0;
}

int main() {
    int exit(0);
    int count(0);
    Wr.CreateSem();
    Re.CreateSem();
    M.CreateM();

    while(exit != 5) {
        cout << "Menu" << endl;
        cout << "1 - Add items in shared resource" << endl;
        cout << "2 - Add writer" << endl;
        cout << "3 - Add reader" << endl;
        cout << "4 - Start thread" << endl;
        cout << "5 - Exit" << endl;
        cin >> exit;

        switch(exit) {
            case 1: {
                Object = AddInEnd(Object);
                break;
            }
            case 2: {
                writers = AddThreadInEnd(writers, WriterM, count);
                count++;
                break;
            }
            case 3: {
                readers = AddThreadInEnd(readers, ReaderM, count);
                count++;
                break;
            }
            case 4: {
                Start(writers, time0);
                Start(readers, time0);
                break;
            }
        }
    }

    return 0;
}
*/
