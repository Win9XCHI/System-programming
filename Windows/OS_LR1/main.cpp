#include <ctime>
#include "flow.h"
#include "critsec.h"
#include "linelistoperations.h"

CritSec CS;
DWORD time0 = INFINITE;
Node *Object = nullptr;

DWORD WINAPI Reader(PVOID pvParam) {
    CS.Entrance();

    cout << endl << "Number thread: " << (int)pvParam;
    cout << endl << "Amount of elements - " << CountNode(Object) << endl;
    Output(Object);

    CS.Exit();
    Sleep(1000);
    time0 = 0;
}

DWORD WINAPI Writer(PVOID pvParam) {
    CS.Entrance();

    cout << endl << "Number thread: " << (int)pvParam;
    Object = AddInEnd(Object);

    CS.Exit();
    Sleep(1000);
    time0 = 0;
}

int main() {
    NodeThread *writers = nullptr;
    NodeThread *readers = nullptr;
    int exit(0);
    int count(0);

    CS.CreateCritSec();

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
                writers = AddThreadInEnd(writers, Writer, count);
                count++;
                break;
            }
            case 3: {
                readers = AddThreadInEnd(readers, Reader, count);
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

    CS.DeleteCritSec();

    return 0;
}
