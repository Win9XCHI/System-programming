#include <iostream>
#include "file.h"
#include "event.h"
#include "mutex.h"

using namespace std;

bool terminated = false;
Mutex OMutex(nullptr, FALSE, (PCTSTR)L"NMutex");
Event OEvent(nullptr, FALSE, TRUE, (PCTSTR)L"NEvent");
File ReadWrite((LPCWSTR)L"File.dat");

BOOL WINAPI consoleHandler(DWORD signal) {

    if (signal == CTRL_C_EVENT) {
        cout << "\nCtrl-C handled\n";
        terminated = true;
        OMutex.AddCountMut();
        Sleep(1000);
        exit(0);
    }

    return TRUE;
}

int main() {
    bool flag = false;

    if (!OMutex.Open(MUTEX_ALL_ACCESS, FALSE)) {
         if (!OMutex.CreateM()) {
             cout << endl << "Mutex false" << endl << "Error code: " << GetLastError();
             flag = true;
         }
     }

    if (!OEvent.Open(MUTEX_ALL_ACCESS, FALSE)) {
        if (!OEvent.CreateE()) {
            cout << endl << "Event false" << endl << "Error code: " << GetLastError();
            flag = true;
        }
    }

    if(!ReadWrite.OpenFM(FILE_MAP_READ | FILE_MAP_WRITE, FALSE)) {
        CFM str2;
        if (!ReadWrite.CreateFM(str2)) {
             cout << endl << "Create file mapping false" << endl << "Error code: " << GetLastError();
             ReadWrite.Close();
             flag = true;
        }
    }
    mVoF str3;
    if (!ReadWrite.MVOF(str3)) {
        cout << endl << "MapViewOfFile false" << endl << "Error code: " << GetLastError();
        ReadWrite.Close();
        flag = true;
    }

     cout << endl << endl << "HANDLE mutex: " << OMutex.GetMutex();
     cout << endl << "HANDLE event: " << OEvent.GetEvent();
     cout << endl << "HANDLE file: " << ReadWrite.GetFile();
     cout << endl << "HANDLE file mapping: " << ReadWrite.GetFileMap();
     cout << endl << "PVOID map view: " << ReadWrite.GetMV() << endl;

     if (flag) {
         exit(0);
     }

     HANDLE hEventAndMutex[2];
     hEventAndMutex[0] = OEvent.GetEvent();
     hEventAndMutex[1] = OMutex.GetMutex();

     while (!terminated) {
         DWORD result;
         result = WaitForMultipleObjects(2, hEventAndMutex, TRUE, INFINITE);

         if (result == WAIT_OBJECT_0) {
             cout << endl << "Text: ";
             ReadWrite.Read();
         }   
         OMutex.AddCountMut();

         if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
               cout << "\nERROR: Could not set control handler";
          }
         Sleep(10);
     }

     return 0;
}

