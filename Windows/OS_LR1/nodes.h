#ifndef NODES_H
#define NODES_H
#include "flow.h"

//Структура вузла списку
struct Node {
    int info; //інвормаційна частина
    Node *next; //вказівник на наступний елемент
    Node *previous; //вказівник на попередній елемент
};

struct NodeThread {
    flow *info; //інвормаційна частина
    int number;
    NodeThread *next; //вказівник на наступний елемент
};

/*struct sharedResource {
    CritSec CS;
    Node *head;
    DWORD time0 = INFINITE;
};*/

#endif // NODES_H
