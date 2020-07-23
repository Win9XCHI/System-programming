#include "pch.h"
#include "DllDefine.h"

#define MAX_INT 255

using namespace std;

//Додавання елементів в кінець
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *AddInEnd(Node *head) {
	int rab;
	char buff[MAX_INT], c('y');
	Node *work;
	Node *last;
	last = head;

	if (head != NULL) {
		while (last->next != NULL) {
			last = last->next;
		}
	}

	while (c == 'y') {
		work = new Node;
		work->next = NULL;
		work->previous = last;

		if (head != NULL) {
			last->next = work;
		}
		else {
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

//Додавання елемента перед елементом із заданим значенням
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *AddBeforeItems(Node *head) {
	int rab;
	char buff[MAX_INT];
	Node *work;
	Node *work2;
	work2 = head;
	double num(0);

	cout << endl << "Enter num: ";
	cin >> buff;
	num = atoi(buff);

	while (work2 != NULL) {
		if (work2->info == num) {
			work = new Node;
			work->next = work2;
			work->previous = work2->previous->previous;
			cout << endl << "Enter info:  ";
			cin >> buff;
			rab = atoi(buff);
			work->info = rab;

			work2->previous->next = work;
			work2->previous = work;
		}
		work2 = work2->next;
	}

	return head;
}

//Видалення пергошо елемента списку
//Вхідні дані: вказівник на перший головний елемент типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *DeleteFirstItem(Node *head) {
	Node *work;
	work = head;
	head = work->next;
	if (head != nullptr) {
		head->previous = NULL;
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

	while (work != nullptr) {

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
	while (work != NULL) {
		cout << i << " - " << work->info << endl;
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

	while (work != NULL) {
		head = work->next;
		delete work;
		work = head;
	}
	head = work;
	return head;
}

//Формування нового списку
//Вхідні дані: вказівники на перші головні елементи списку типу Node
//та вказівник на перший елемент нового списку
//Вихідні дані: вказівник на головний елемент типу Node
Node *Sym(Node *work, Node *list2, Node *head) {
	Node *last, *work2;
	bool flag = false;
	last = head;
	work2 = list2;

	if (head != NULL) {
		while (last->next != NULL) {
			last = last->next;
		}
	}

	while (work != NULL) {

		while (work2 != NULL) {
			if (work2->info == work->info) {
				flag = true;
			}
			work2 = work2->next;
		}

		if (!flag) {
			work2 = new Node;
			work2->next = NULL;
			work2->previous = last;

			if (head != NULL) {
				last->next = work2;
			}
			else {
				head = work2;
			}
			work2->info = work->info;
			last = work2;
		}
		else {
			flag = false;
		}

		work2 = list2;
		work = work->next;
	}

	return head;
}

//Сортування Хоара
//Вхідні дані: вказівник на перший та останній елемент списку типу Node
//Вихідні дані відсутні
void HoaraSort(Node *first, Node *last) {
	Node *i, *j;
	i = first;
	j = last;
	double tmp, x = first->info;
	do {
		while (i->info < x) {
			i = i->next;
		}
		while (j->info > x) {
			j = j->previous;
		}

		if (i->info > j->info) {
			tmp = i->info;
			i->info = j->info;
			j->info = tmp;

			if (i->info == j->info && i->next != j->next) {
				i = i->next;
				j = j->previous;
			}
		}
		else {
			i = i->next;
			j = j->previous;
		}
	} while (i->info < j->info);

	if (i->info > last->info && i < last)  HoaraSort(i, last);
	if (first->info > j->info && first < j) HoaraSort(first, j);
}

//Симетрична різниця двох списків
//Вхідні дані: вказівники на перші головні елементи списку типу Node
//Вихідні дані: вказівник на головний елемент типу Node
Node *SymDif(Node *head1, Node *head2) {
	Node *headSym;
	Node *last;
	headSym = NULL;

	headSym = Sym(head1, head2, headSym);
	headSym = Sym(head2, head1, headSym);

	if (headSym != NULL) {
		last = headSym;

		while (last->next != NULL) {
			last = last->next;
		}

		HoaraSort(headSym, last);
	}
	else {
		cout << endl << "Not Symmetrical difference" << endl;
	}


	return headSym;
}
