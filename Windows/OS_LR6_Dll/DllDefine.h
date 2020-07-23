#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

//Структура вузла списку
struct Node {
	double info; //інвормаційна частина
	Node *next; //вказівник на наступний елемент
	Node *previous; //вказівник на попередній елемент
};

//Додавання елементів в кінець
	//Вхідні дані: вказівник на перший головний елемент типу Node
	//Вихідні дані: вказівник на головний елемент типу Node
extern "C" MATHLIBRARY_API Node *AddInEnd(Node *);

//Додавання елемента перед елементом із заданим значенням
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
extern "C" MATHLIBRARY_API Node *AddBeforeItems(Node *);

//Видалення пергошо елемента списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
extern "C" MATHLIBRARY_API Node *DeleteFirstItem(Node *);

//Видалення елемента списку по порядковому номеру
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
extern "C" MATHLIBRARY_API Node *DeleteItemNumber(Node *);

//Виведення списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані відсутні
extern "C" MATHLIBRARY_API void Output(Node *);

//Видалення списка
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
extern "C" MATHLIBRARY_API Node *DeleteList(Node *);

//Симетрична різниця двох списків
//Вхідні дані: вказівники на перші головні елементи списку типу Node
//Вихідні дані: вказівник на головний елемент типу Node
extern "C" MATHLIBRARY_API Node *SymDif(Node *, Node *);

//Сортування Хоара
//Вхідні дані: вказівник на перший та останній елемент списку типу Node
//Вихідні дані відсутні
extern "C" MATHLIBRARY_API void HoaraSort(Node *, Node *);

//Формування нового списку
	//Вхідні дані: вказівники на перші головні елементи списку типу Node
	//та вказівник на перший елемент нового списку
	//Вихідні дані: вказівник на головний елемент типу Node
Node *Sym(Node *, Node *, Node *);