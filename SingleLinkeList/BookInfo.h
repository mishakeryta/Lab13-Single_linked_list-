#ifndef BOOK_INFO_HEADER
#define BOOK_INFO_HEADER
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_NAMES 71
typedef struct SBookInfo
{
	char author[SIZE_NAMES];
	char name[SIZE_NAMES];
	int year;
	int pages;
	double price;
}BookInfo;
//����� ������ ������� FReadBoolInfo
#define BUFFER_SIZE 1000
//�������,��� ����� ��� � ������(���������, ����� ������������) 
int FReadBookInfo(BookInfo* info, FILE* inptr);

// �������, ��� ������ ���, �����, ���� ��� ����� ������� 1,������ ������� 0
int FPrintBookInfo(BookInfo info, FILE* outptr);

//���� ����� �������, ����� 1, ������ 0
int IsBooksEqual(BookInfo book1, BookInfo book2);
#endif
