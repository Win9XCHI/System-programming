// WindowsProject1.cpp : Определяет точку входа для приложения.
//

#include <cstdlib>
#include "framework.h"
#include "WindowsProject1.h"


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
//WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
//WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

LPCWSTR szTitle = L"LR5_2";
LPCWSTR szWindowClass = L"LR5_2";

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);



    // Инициализация глобальных строк
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    HWND OutherWindow = FindWindow(NULL, L"OutherWindow");

    if (OutherWindow != NULL) {

    }

    //MessageBox(NULL, L"Call to CreateWindow failed!", L"Message", NULL);

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    HWND hWnd_edit1 = CreateWindow(L"Edit", L"Введите текст", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 5, 100, 30, hWnd, (HMENU)3, hInstance, NULL);
    HWND hWnd_button1 = CreateWindow(L"button", L"Очистить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 50, 150, 30, hWnd, (HMENU)1, hInstance, NULL);
    HWND hWnd_button2 = CreateWindow(L"button", L"Передать текст", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 160, 50, 300, 30, hWnd, (HMENU)2, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Message", NULL);
        return FALSE;
    }
    //MoveWindow(hWnd, 700, 100, 500, 120, TRUE);


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        break;
    case WM_COPYDATA: {
        PCOPYDATASTRUCT s = (PCOPYDATASTRUCT)lParam;
        hdc = BeginPaint(hWnd, &ps);
        SetDlgItemText(hWnd, 3, (LPCWSTR)(void*)s->lpData);
        EndPaint(hWnd, &ps);
        break; }
    case WM_COMMAND:
    { if (LOWORD(wParam) == 1)
    {
        hdc = BeginPaint(hWnd, &ps);
        SetDlgItemText(hWnd, 3, L"");
        EndPaint(hWnd, &ps);
    }
    if (LOWORD(wParam) == 2) {
        wchar_t* str = new wchar_t[50];
        GetDlgItemText(hWnd, 3, str, 50);
        str[wcslen(str)] = '\0';
        COPYDATASTRUCT cd;
        cd.dwData = 0;
        cd.cbData = wcslen(str) + 1;
        cd.lpData = str;

        HWND hRecieverWnd = FindWindow(NULL, L"LR5_1");
        if (hRecieverWnd != 0)
        {
            SendMessage(hRecieverWnd, WM_COPYDATA, 0, (LPARAM)&cd);
        }
        else
            MessageBox(NULL, L"Not create window", L"Message", NULL);
    }
    break; }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
