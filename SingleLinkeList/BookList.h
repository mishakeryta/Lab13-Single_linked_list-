#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookInfo.h"
typedef struct Snode
{
	TbookInfo m_info;
	struct Snode *m_pNext;
}Snode;
//������ ����� �������, � �������� ���'��
Snode* CreateNew(TbookInfo data);
//�������� data ,���� ��� ��������� ������� ������,� ��������� ����(����� �������);
int InsertNewInOrder(Snode** list, TbookInfo info);
//������� �� ����� � ������� ������� ����� 50 
int DeleteLess50Pages(Snode** list);
//���� ������� ����� ������
//��������� � ������ 5 ��������� ����,������ �� � ���������� �����, �������� �� ���� �������
TbookInfo* FindTop5Latest(const Snode* list);
//������� ������
int DeleteList(Snode** list);
//����� ����� �� ������� ������, ������� ����, ���� ��� �������
//�����(�������) ����������
void PrintListBooks(const Snode* booksNode);
int  PrintListBooksToFile(const Snode* list, const char* szPath);
int DeleteHead(Snode** ppHeadOfList);
int CountNodes(const Snode* pList);

#endif
