#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include "PrintListBook.h"
static void PrintRows(int iNum1, ...) {
	putchar('+');
	va_list list;
	va_start(list, iNum1);
	int iNumRow = 0;
	for (int i = 0; i < iNum1; i++) {
		iNumRow = va_arg(list, int);
		for (int j = 0; j < iNumRow; ++j) {
			putchar('-');
		}
		putchar('+');
	}
	va_end(list);
	printf("\n");
}
void PrintTemplate(void) {
	printf("|%-*s|", 27, "Author");
	printf("%-*s|", 25, "Name");
	printf("%*s|", 6, "Year");
	printf("%*s|", 5, "Pages");
	printf("%*s|\n", 6, "Price");
}
void PrintBookInfo(BookInfo data) {
	printf("|%-*s|", 27, data.author);
	printf("%-*s|", 25, data.name);
	printf("%*i|", 6, data.year);
	printf("%*i|", 5, data.pages);
	printf("%*.2lf|\n", 6, data.price);
}
void PrintListBooks(const Node* booksNode) {
	if (!booksNode) {
		return;
	}
	PrintRows(5, 27, 25, 6, 5, 6);
	PrintTemplate();
	PrintRows(5, 27, 25, 6, 5, 6);
	do {
		PrintBookInfo(booksNode->info);
		PrintRows(5, 27, 25, 6, 5, 6);
		booksNode = booksNode->next;
	} while (booksNode);
}
void PrintArrayBooks(const BookInfo* arrBooksInfo, int num) {
	if (!arrBooksInfo) {
		return;
	}
	PrintRows(5, 27, 25, 6, 5, 6);
	PrintTemplate();
	PrintRows(5, 27, 25, 6, 5, 6);
	for (int i = 0; i < num; ++i) {
		PrintBookInfo(arrBooksInfo[i]);
		PrintRows(5, 27, 25, 6, 5, 6);
	}
}
//вставляє вміст списку у файл(звісно вміст зюерігається у відповідному форматі)
//попередній вміст файлу стирається
int FPrintListBooks(const Node* list, const char* path) {
	if (!path) return 0;
	//стираємо попередній вміст файлу
	FILE*  outptr = fopen(path, "w");
	if (!outptr)  return 0;
	fclose(outptr);
	outptr = fopen(path, "a");
	while (list) {
		FPrintBookInfo(list->info, outptr);
		list = list->next;
	}
	fclose(outptr);
	return 1;
}