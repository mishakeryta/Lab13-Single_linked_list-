#ifndef BOOK_INFO_HEADER
#define BOOK_INFO_HEADER
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//кільість колонок в таблиці
#define NUM_OF_COLS 5
//Максимальна довжина імен ,яку може зберігати ТboolInfo. 
#define SIZE_NAMES 71
#define SIZE_OF_COL_WITH_NAMES 26
#define SIZE_OF_COL_WITH_NUMBERS 6
//Тип, що зберігає дані про книгу.
typedef struct TbookInfo
{
	char szAuthor[SIZE_NAMES];
	char szName[SIZE_NAMES];
	int nPages;
	int nYear;
	double dPrice;
}TbookInfo;

//Розмір буферу функції FReadBoolInfo.
//Максимальна довжина ,яку користувач може ввести в одному рядку.
#define BUFFER_SIZE 1000

//максимальна довжина чила в символах включно з '-' 
#define MAX_LENGHT_OF_NUMBER 6
//функція,яка зчитує дані з потуку(будьякого, навіть стандартного) 
//Приклад використання:
//TbookInfo info = {0};
//ReadBookInfo(info,stdio);
int ReadBookInfoFromFile(TbookInfo* info, FILE* pfInput);
//--------------------------------------------------------------------------------
//Виводить рядок у форматі
//+-----+-----+----+\n(прехід на новий рядок).
//Де кількість проміжків між '+' дорівнює nNum
//А всі наступні аргументи ,кількість яких дорівнює nNum,позначають відстані
//між цими плюсами.
//Приклад:
//PrintRows(3,2,2,3);
//Вивід на екран(консоль):
//+--+--+---+\n(прехід на новий рядок)
void PrintRows(int nNum, ...);
//--------------------------------------------------------------------------------
//Макрос який просто виводить рядок таблиці
#define PRINT_ROW_FOR_BOOK_TABLE() PrintRows(NUM_OF_COLS \
,SIZE_OF_COL_WITH_NAMES \
,SIZE_OF_COL_WITH_NAMES \
,SIZE_OF_COL_WITH_NUMBERS \
,SIZE_OF_COL_WITH_NUMBERS \
,SIZE_OF_COL_WITH_NUMBERS)
//--------------------------------------------------------------------------------
// Виводить на екран верхній ряд таблиці, з визначеннями колонок.
void PrintTemplate(void);
//--------------------------------------------------------------------------------
//Виводить книгу на екран у форматі:
//|szAuthor|szName|nYear|nPages|dPrice|(новий рядок)
void PrintBook(TbookInfo info);
//--------------------------------------------------------------------------------
//Виводить масив книг у вигляді таблиці з видимими рамками.
void PrintArrayBooks(TbookInfo* pInfo, int nNum);
//--------------------------------------------------------------------------------
//якщо книги однакові, вертає 1, інакше 0
int IsBooksEqual(TbookInfo info1, TbookInfo info2);
//--------------------------------------------------------------------------------
#endif
