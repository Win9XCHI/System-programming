#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif

#include <iostream>

//��������� ����� ������
struct Node {
	double info; //������������ �������
	Node *next; //�������� �� ��������� �������
	Node *previous; //�������� �� ��������� �������
};

//��������� �������� � �����
	//����� ���: �������� �� ������ �������� ������� ���� Node
	//������ ���: �������� �� �������� ������� ���� Node
extern "C" MATHLIBRARY_API Node *AddInEnd(Node *);

//��������� �������� ����� ��������� �� ������� ���������
//����� ���: �������� �� ������ �������� ������� ���� Node
//������ ���: �������� �� �������� ������� ���� Node
extern "C" MATHLIBRARY_API Node *AddBeforeItems(Node *);

//��������� ������� �������� ������
//����� ���: �������� �� ������ �������� ������� ���� Node
//������ ���: �������� �� �������� ������� ���� Node
extern "C" MATHLIBRARY_API Node *DeleteFirstItem(Node *);

//��������� �������� ������ �� ����������� ������
//����� ���: �������� �� ������ �������� ������� ���� Node
//������ ���: �������� �� �������� ������� ���� Node
extern "C" MATHLIBRARY_API Node *DeleteItemNumber(Node *);

//��������� ������
//����� ���: �������� �� ������ �������� ������� ���� Node
//������ ��� ������
extern "C" MATHLIBRARY_API void Output(Node *);

//��������� ������
//����� ���: �������� �� ������ �������� ������� ���� Node
//������ ���: �������� �� �������� ������� ���� Node
extern "C" MATHLIBRARY_API Node *DeleteList(Node *);

//���������� ������ ���� ������
//����� ���: ��������� �� ����� ������ �������� ������ ���� Node
//������ ���: �������� �� �������� ������� ���� Node
extern "C" MATHLIBRARY_API Node *SymDif(Node *, Node *);

//���������� �����
//����� ���: �������� �� ������ �� ������� ������� ������ ���� Node
//������ ��� ������
extern "C" MATHLIBRARY_API void HoaraSort(Node *, Node *);

//���������� ������ ������
	//����� ���: ��������� �� ����� ������ �������� ������ ���� Node
	//�� �������� �� ������ ������� ������ ������
	//������ ���: �������� �� �������� ������� ���� Node
Node *Sym(Node *, Node *, Node *);