#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookInfo.h"
typedef struct Snode
{
	BookInfo m_info;
	struct Snode *m_pNext;
}Snode;

//������ ����� �������, � �������� ���'��
Snode* CreateNew(BookInfo data);
//�������� data ,���� ��� ��������� ������� ������,� ��������� ����(����� �������);
int InsertNewInOrder(Snode** list, BookInfo info);
//������� �� ����� � ������� ������� ����� 50 
int DeleteLess50Pages(Snode** list);
//���� ������� ����� ������
int CountNodes(const Snode* list);
//��������� � ������ 5 ��������� ����,������ �� � ���������� �����, �������� �� ���� �������
BookInfo* FindTop5Latest(const Snode* list);
//������� ������
int DeleteList(Snode** list);
Snode* GetNode(Snode* list, int index);

//����� ����� �� ������� ������, ������� ����, ���� ��� �������
int SortBooks(Snode** list);

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
int InsertNewListFromFile(Snode**list, const char*path);

int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second));

int DeleteHead(Snode** head);
#include "PrintListBook.h"
#endif
