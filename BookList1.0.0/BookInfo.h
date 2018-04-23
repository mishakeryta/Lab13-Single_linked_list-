#ifndef BOOK_INFO_HEADER
#define BOOK_INFO_HEADER
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//������� ������� � �������
#define NUM_OF_COLS 5
//����������� ������� ���� ,��� ���� �������� �boolInfo. 
#define SIZE_NAMES 71
#define SIZE_OF_COL_WITH_NAMES 26
#define SIZE_OF_COL_WITH_NUMBERS 6
//���, �� ������ ��� ��� �����.
typedef struct TbookInfo
{
	char szAuthor[SIZE_NAMES];
	char szName[SIZE_NAMES];
	int nPages;
	int nYear;
	double dPrice;
}TbookInfo;

//����� ������ ������� FReadBoolInfo.
//����������� ������� ,��� ���������� ���� ������ � ������ �����.
#define BUFFER_SIZE 1000

//����������� ������� ���� � �������� ������� � '-' 
#define MAX_LENGHT_OF_NUMBER 6
//�������,��� ����� ��� � ������(���������, ����� ������������) 
//������� ������������:
//TbookInfo info = {0};
//ReadBookInfo(info,stdio);
int ReadBookInfoFromFile(TbookInfo* info, FILE* pfInput);
//--------------------------------------------------------------------------------
//�������� ����� � ������
//+-----+-----+----+\n(������ �� ����� �����).
//�� ������� ������� �� '+' ������� nNum
//� �� ������� ��������� ,������� ���� ������� nNum,���������� ������
//�� ���� �������.
//�������:
//PrintRows(3,2,2,3);
//���� �� �����(�������):
//+--+--+---+\n(������ �� ����� �����)
void PrintRows(int nNum, ...);
//--------------------------------------------------------------------------------
//������ ���� ������ �������� ����� �������
#define PRINT_ROW_FOR_BOOK_TABLE() PrintRows(NUM_OF_COLS \
,SIZE_OF_COL_WITH_NAMES \
,SIZE_OF_COL_WITH_NAMES \
,SIZE_OF_COL_WITH_NUMBERS \
,SIZE_OF_COL_WITH_NUMBERS \
,SIZE_OF_COL_WITH_NUMBERS)
//--------------------------------------------------------------------------------
// �������� �� ����� ������ ��� �������, � ������������ �������.
void PrintTemplate(void);
//--------------------------------------------------------------------------------
//�������� ����� �� ����� � ������:
//|szAuthor|szName|nYear|nPages|dPrice|(����� �����)
void PrintBook(TbookInfo info);
//--------------------------------------------------------------------------------
//�������� ����� ���� � ������ ������� � �������� �������.
void PrintArrayBooks(TbookInfo* pInfo, int nNum);
//--------------------------------------------------------------------------------
//���� ����� �������, ����� 1, ������ 0
int IsBooksEqual(TbookInfo info1, TbookInfo info2);
//--------------------------------------------------------------------------------
#endif
