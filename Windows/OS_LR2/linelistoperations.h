#ifndef LINELISTOPERATIONS_H
#define LINELISTOPERATIONS_H
#include <iostream>
#include "nodes.h"
#include "semaphore.h"
#define MAX_INT 255

using namespace std;

//Функції для роботи зі списком

//Додавання елементів в кінець
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *AddInEnd(Node *);

NodeThread *AddThreadInEnd(NodeThread *, LPTHREAD_START_ROUTINE, int);

void Start(NodeThread *, DWORD);

//Видалення пергошо елемента списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteFirstItem(Node *);

//Видалення елемента списку по порядковому номеру
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteItemNumber(Node *);

//Виведення списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані відсутні
void Output(Node *);

//Видалення списка
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteList(Node *);

int CountNode(Node *);

#endif // LINELISTOPERATIONS_H
