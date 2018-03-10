#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookInfo.h"
typedef struct SNode
{
	BookInfo info;
	struct SNode *next;
}Node;

//������ ����� �������, � �������� ���'��
Node* CreateNew(BookInfo data);
//�������� data ,���� ��� ��������� ������� ������,� ��������� ����(����� �������);
int InsertNewInOrder(Node** list, BookInfo data);
//������� �� ����� � ������� ������� ����� 50 
int DeleteLess50Pages(Node** list);
//���� ������� ����� ������
int CountNodes(const Node* list);
//��������� � ������ 5 ��������� ����,������ �� � ���������� �����, �������� �� ���� �������
BookInfo* FindTop5Latest(const Node* list);
//������� ������
int DeleteList(Node** list);
Node* GetNode(Node* list, int index);

//����� ����� �� ������� ������, ������� ����, ���� ��� �������
int SortBooks(Node** list);

//�����(�������) ����������
int ByAlphabetAuthors(const BookInfo* first, const BookInfo* second);

int NotByAlphabetAuthors(const BookInfo* first, const BookInfo* second);

int ByAlphabetName(const BookInfo* first, const BookInfo* second);

int NotByAlphabetName(const BookInfo* first, const BookInfo* second);
int ByIncreasingPrice(const BookInfo* first, const BookInfo* second);

int ByReducingPrice(const BookInfo* first, const BookInfo* second);

int ByIncreasingYear(const BookInfo* first, const BookInfo* second);

int ByReducingYear(const BookInfo* first, const BookInfo* second);

int ByIncreasingPages(const BookInfo* first, const BookInfo* second);

int ByReducingPages(const BookInfo* first, const BookInfo* second);
int InsertNewListFromFile(Node**list, char*path);

int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second));
#include "PrintListBook.h"
#endif
