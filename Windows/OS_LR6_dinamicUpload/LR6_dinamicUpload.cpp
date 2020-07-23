/* Написати програму для виконання операцій над лінійним двозв’язним списком відповідно до індивідуального завдання. Програма повинна мати текстове меню, складатися з модулів.
Реалізувати:
1	Додати елемент в кінець списку.
2	Вставити елемент перед елементом з заданим значенням.
3	Видалити перший елемент.
4	Видалити елемент з заданим порядковим номером.
5	Симетрична різниця двох списків.
6	Вивести значення всіх елементів списку.
Вхідні дані: дійсні числа.
Вихідні дані: список дійсних чисел.
*/
#include <iostream>
#include <Windows.h>
#include "file.h"
#define MAX_INT 255

using namespace std;

int TwoMenu() {
    int exit(0);
    char buff[MAX_INT];

    cout << "Menu" << endl;
    cout << "1 - List 1" << endl;
    cout << "2 - List 2" << endl;
    cout << "3 - Exit" << endl;
    cin >> buff;
    exit = atoi(buff);

    return exit;
}

int main() {
    char buff[MAX_INT];
    char c;
        Node *headFirst; //Перший список
        Node *headTwo; //Другий список
        Node *job(nullptr); //Робочий список
        FILE *file(nullptr);
        headFirst = NULL;
        headTwo = NULL;
        int exit(1), i(-1);

		Node *(__stdcall *AddInEnd)(Node *);
		Node *(__stdcall *AddBeforeItems)(Node *);
		Node *(__stdcall *DeleteFirstItem)(Node *);
		Node *(__stdcall *DeleteItemNumber)(Node *);
		void(__stdcall *Output)(Node *);
		Node *(__stdcall *DeleteList)(Node *);
		Node *(__stdcall *SymDif)(Node *, Node *);
		void(__stdcall *HoaraSort)(Node *, Node *);

		HINSTANCE hLib = LoadLibrary(L"../../LR6_Dll/Release/LR6_Dll.DLL");
		if (!hLib) {
			cout << "Unable to load library!" << endl;
			return 1;
		}
		AddInEnd = (Node *(__stdcall *) (Node *))GetProcAddress(hLib, "AddInEnd");
		AddBeforeItems = (Node *(__stdcall *) (Node *))GetProcAddress(hLib, "AddBeforeItems");
		DeleteFirstItem = (Node *(__stdcall *) (Node *))GetProcAddress(hLib, "DeleteFirstItem");
		DeleteItemNumber = (Node *(__stdcall *) (Node *))GetProcAddress(hLib, "DeleteItemNumber");
		Output = (void(__stdcall *) (Node *))GetProcAddress(hLib, "Output");
		DeleteList = (Node *(__stdcall *) (Node *))GetProcAddress(hLib, "DeleteList");
		SymDif = (Node *(__stdcall *) (Node *, Node *))GetProcAddress(hLib, "SymDif");
		HoaraSort = (void(__stdcall *) (Node *, Node *))GetProcAddress(hLib, "HoaraSort");

		if (!AddInEnd || !AddBeforeItems || !DeleteFirstItem || !DeleteItemNumber || !Output || !DeleteList || !SymDif || !HoaraSort) {
			cout << "Unable to load functions!" << endl;
			cout << AddInEnd << " " << AddBeforeItems << " " << DeleteFirstItem << " " << DeleteItemNumber << " " << Output << " " << DeleteList << " " << SymDif << " " << HoaraSort;
			return 1;
		}
		

        while(exit != 9) {
            cout << "Menu" << endl;
            cout << "1 - Add items in end" << endl;
            cout << "2 - Add item before items with a given value" << endl;
            cout << "3 - Delete first item" << endl;
            cout << "4 - Delete item with number" << endl;
            cout << "5 - Symmetrical difference lists" << endl;
            cout << "6 - Output list" << endl;
            cout << "7 - Save list in file" << endl;
            cout << "8 - Read list from file" << endl;
            cout << "9 - Exit" << endl;
            cin >> buff;
            exit = atoi(buff);

            if (exit != 9 && exit != 5) {
                i = TwoMenu();
                if (i == 1) {
                    job = headFirst;
                }
                if (i == 2) {
                    job = headTwo;
                }
                if (i == 3 || i == 0) {
                    exit = 0;
                }
            }
            switch(exit) {
                case 1: {
					job = AddInEnd(job);
                    break;
                }
                case 2: {
                    if (job == NULL) {
                        exit = 0;
                    } else {
						job = AddBeforeItems(job);
                    }

                    if (exit == 0) {
                        cout << endl << "List is empty" << endl;
                    }

                    break;
                }
                case 3: {
                    if (job == NULL) {
                        exit = 0;
                    } else {
						job = DeleteFirstItem(job);
                    }

                    if (exit == 0) {
                        cout << endl << "List is empty" << endl;
                    }
                    break;
                }
                case 4: {
                    if (job == NULL) {
                        exit = 0;
                    } else {
						job = DeleteItemNumber(job);
                    }

                    if (exit == 0) {
                        cout << endl << "List is empty" << endl;
                    }
                    break;
                }
                case 5: {
                    if (headFirst == NULL || headTwo == NULL) {
                        exit = 0;
                    } else {
                        job = SymDif(headFirst, headTwo);
                        Output(job);
                        DeleteList(job);
                    }

                    if (exit == 0) {
                        cout << endl << "List is empty" << endl;
                    }
                    break;
                }
                case 6: {
                    if (job == NULL) {
                        exit = 0;
                    } else {
                        Output(job);
                    }

                    if (exit == 0) {
                        cout << endl << "List is empty" << endl;
                    }
                    break;
                }
                case 7: {
                    if (job == NULL) {
                        exit = 0;
                    } else {
                        Save(file, job);
                    }

                    if (exit == 0) {
                        cout << endl << "List is empty" << endl;
                    }
                    break;
                }
                case 8: {
                    job = Read(file);
                    break;
                }
                case 9: {
                    if (headFirst != NULL || headTwo != NULL) {
                        cout << endl << "Delete list 1 and 2? (y/n)" << endl;
                        cin >> c;

                        if (c == 'y') {
                            DeleteList(headFirst);
                            DeleteList(headTwo);
                        } else {
                            exit = 0;
                        }
                    }
                    break;
                }
            }
            if (exit != 9 && exit != 5) {
                if (i == 1) {
                    headFirst = job;
                }
                if (i == 2) {
                    headTwo = job;
                }
            }
        }

		FreeLibrary(hLib);
    return 0;
}
