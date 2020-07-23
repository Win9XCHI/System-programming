// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "DllDefine.h"

int CountelemProc = 0;
int CountelemThr = 0;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     ) {
    switch (ul_reason_for_call) {

		case DLL_PROCESS_ATTACH: {
			
			if (CountelemProc > 2)	{
				MessageBox(NULL, L"Not Limit PROCESS", L"error", MB_OK);	
				return FALSE;
			}
			CountelemProc++;
			break;
		}

		case DLL_THREAD_ATTACH: {

			if (CountelemThr > 2) {
				MessageBox(NULL, L"Not Limit THREAD", L"error", MB_OK);	
				return FALSE;
			}
			CountelemThr++;
			break;
		}

		case DLL_THREAD_DETACH: {

			if (CountelemThr == 0) {
				return FALSE;
			}
			CountelemThr--;
			break;
		}

		case DLL_PROCESS_DETACH: {
			if (CountelemProc == 0) {
				return FALSE;
			}
			CountelemProc--;
			break;
		}
        break;
    }
    return TRUE;
}
