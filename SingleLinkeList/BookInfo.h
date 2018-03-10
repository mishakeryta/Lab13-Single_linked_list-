#ifndef BOOK_INFO_HEADER
#define BOOK_INFO_HEADER
#include <stdio.h>

#define SIZE_NAMES 71
typedef struct SBookInfo
{
	char author[SIZE_NAMES];
	char name[SIZE_NAMES];
	int year;
	int pages;
	double price;
}BookInfo;

//розмір буферу функції FReadBoolInfo
#define BUFFER_SIZE 1000
//функція,яка зчитує дані з потуку(будьякого, навіть стандартного) 
int FReadBookInfo(BookInfo* info, FILE* inptr);
#endif
