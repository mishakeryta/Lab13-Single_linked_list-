#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BookList.h"
#include "PrintListBook.h"

int main(void) {
	BookInfo book = { 0 };
	Node* listOfBooks = NULL;
	FILE* inptr = fopen("Books.txt", "r");
	int noEnd = 0;
	char der[10];
	while(noEnd = FReadBookInfo(&book, inptr)) {
		if (noEnd == 1) {
			InsertNewInOrder(&listOfBooks, book);
		}
	};
	PrintListBooks(listOfBooks);
	//DeleteLess50Pages(&listOfBooks);
	//PrintListBooks(listOfBooks);
	//BookInfo* top5LatesBooks = FindTop5Latest(listOfBooks);
	//PrintArrayBook(top5LatesBooks, 5);
	DeleteList(&listOfBooks);
	//free(top5LatesBooks);
	getchar(); getchar();
	return 0;
}