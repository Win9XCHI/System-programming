#include <iostream>
#include <Windows.h>
#include <string>
//#include <thread>
using namespace std;

CRITICAL_SECTION section;

struct context
{
	bool terminated;
	int id;
};

context t1, t2;
HANDLE th1;
HANDLE th2;



DWORD WINAPI ThreadProc(LPVOID lpParam) {
	context* c = (context*)lpParam;
	while(!c->terminated) {

		EnterCriticalSection(&section);
		cout << c->id << endl;
		LeaveCriticalSection(&section);
		Sleep(1000);
	}
	cout << "Terminated: " << c->id << endl;
	return 0;
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType) {
	if (dwCtrlType == CTRL_C_EVENT) {
		t1.terminated = true;
		t2.terminated = true;
		Sleep(1000);
		CloseHandle(th1);
		CloseHandle(th2);
	}
	return true;
}

int main() {
	t1.terminated = false;
	t1.id = 777;
	t2.terminated = false;
	t2.id = 888;
	InitializeCriticalSection(&section);

	th1 = CreateThread(NULL, 0, ThreadProc, &t1, CREATE_SUSPENDED, NULL);
	th2 = CreateThread(NULL, 0, ThreadProc, &t2, CREATE_SUSPENDED, NULL);

	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)HandlerRoutine, true)) {
		cout << "Handler initialized!" << endl;
	}
	else {
		cout << "Faied!" << endl;
	}

	ResumeThread(th1);
	ResumeThread(th2);

	WaitForSingleObject(th1, INFINITE);
	WaitForSingleObject(th2, INFINITE);

	DeleteCriticalSection(&section);


	//thread bth1(pr,"Hello: ", 10);
	//thread bth2(pr, "Hello2: ", 10);
	//if (bth1.joinable())
		//bth1.join();
	//if (bth2.joinable())
		//bth2.join();

	cin.get();
	return 0;
}
