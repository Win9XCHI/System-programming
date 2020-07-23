#include "linelistoperations.h"

int CountNode(Node *head) {
    Node *work;
    work = head;
    int count(0);
    if (head != nullptr) {
        while (work != nullptr) {
            work = work->next;
            count++;
        }
    }
    return count;
}

//Додавання елементів в кінець
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *AddInEnd(Node *head) {
        int rab;
        char buff[MAX_INT], c('y');
        Node *work;
        Node *last;
        last = head;

        if (head != nullptr) {
            while (last->next != nullptr) {
                last = last->next;
            }
        }

        while (c == 'y') {
            work = new Node;
            work->next = nullptr;
            work->previous = last;

            if (head != nullptr) {
                last->next = work;
            } else {
                head = work;
            }
            cout << endl << "Enter info:  ";
            cin >> buff;
            rab = atoi(buff);
            work->info = rab;
            last = work;
            cout << "Enter more? y/n  ";
            cin >> c;
        }

        return head;
}

NodeThread *AddThreadInEnd(NodeThread *head, LPTHREAD_START_ROUTINE name, int number) {
            NodeThread *work;
            NodeThread *last;
            last = head;

            if (head != nullptr) {
                while (last->next != nullptr) {
                    last = last->next;
                }
            }
                work = new NodeThread;
                work->next = nullptr;

                if (head != nullptr) {
                    last->next = work;
                } else {
                    head = work;
                }
                work->info = new flow(number, name);
                work->info->CreateT();
                work->number = number;
                last = work;

            return head;
}

void Start(NodeThread *head, DWORD T) {
    NodeThread *work;
    work = head;

    if (head != nullptr) {
        while (work != nullptr) {
            work->info->ThrStart();
            work = work->next;
        }
    }
}

//Видалення пергошо елемента списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteFirstItem(Node *head) {
    Node *work;
    work = head;
    head = work->next;
    if (head != nullptr) {
        head->previous = nullptr;
    }
    delete work;
    return head;
}

//Видалення елемента списку по порядковому номеру
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteItemNumber(Node *head) {
    int num, i(1);
    Node *work;
    work = head;

    cout << endl << "Enter number: ";
    cin >> num;

    while(work != nullptr) {

        if (i == num) {
            //cout << endl << work->next->previous->info << " " << work->previous->info << " " << work->previous->next->info << " " << work->next->info;
            work->next->previous = work->previous;
            work->previous->next = work->next;
            delete work;
            break;
        }
        work = work->next;
        i++;
    }

    return head;
}

//Виведення списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані відсутні
void Output(Node *head) {
    int i = 1;
    Node *work = head;
    cout << "List:" << endl;
    while(work != nullptr) {
       cout << i <<" - "<< work->info << endl;
       work = work->next;
       i++;
    }
}

//Видалення списка
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteList(Node *head) {
    Node *work;
    work = head;

    while(work != nullptr) {
        head = work->next;
        delete work;
        work = head;
    }
    head = work;
    return head;
}
