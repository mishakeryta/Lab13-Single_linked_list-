#ifndef BOOK_INFO_HEADER
#define BOOK_INFO_HEADER
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#define SIZE_NAMES 71
#define NUM_OF_COLS 5
#define SIZE_OF_COL_WITH_NAMES 26
#define SIZE_OF_COL_WITH_NUMBERS 6
typedef struct TbookInfo
{
	char author[SIZE_NAMES];
	char name[SIZE_NAMES];
	int year;
	int pages;
	double price;
}TbookInfo;

//����� ������ ������� FReadBoolInfo
#define BUFFER_SIZE 1000

//����������� ������� ���� � �������� ������� � '-' 
#define MAX_LENGHT_OF_NUMBER 12
//�������,��� ����� ��� � ������(���������, ����� ������������) 
int ReadBookInfoFromFile(TbookInfo* info, FILE* pfInput);
void PrintRows(int nNum, ...);
#define PRINT_ROW_FOR_BOOKTABLE() PrintRows(NUM_OF_COLS \
,SIZE_OF_COL_WITH_NAMES \
,SIZE_OF_COL_WITH_NAMES \
,SIZE_OF_COL_WITH_NUMBERS \
,SIZE_OF_COL_WITH_NUMBERS \
,SIZE_OF_COL_WITH_NUMBERS)

// �������� �� ����� ������ ��� �������, � ������������ �������.
void PrintTemplate(void);


void PrintBook(TbookInfo info);
void PrintArrayBooks(const TbookInfo* pInfo, int nNum);

//���� ����� �������, ����� 1, ������ 0
int IsBooksEqual(TbookInfo info1, TbookInfo info2);
#endif
