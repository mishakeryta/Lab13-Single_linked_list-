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
//розмір буферу функції FReadBoolInfo
#define BUFFER_SIZE 1000
//функція,яка зчитує дані з потуку(будьякого, навіть стандартного) 
int FReadBookInfo(BookInfo* info, FILE* inptr);

// функція, яка записує дані, употік, якщо все добре повертає 1,інакше повертає 0
int FPrintBookInfo(BookInfo info, FILE* outptr);


int IsBooksEqual(BookInfo book1, BookInfo book2)
{
	if (strcmp(book1.author, book2.author) || strcmp(book1.name,book2.name) ||
		book1.year != book2.year || book1.pages != book2.pages || book1.price != book2.price) return 0;
	return 1;
}
#endif
