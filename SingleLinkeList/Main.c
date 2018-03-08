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
	int indexRowOfFile = 1;
	while(noEnd = FReadBookInfo(&book, inptr)) {
		if (noEnd == 1) {
			InsertNewInOrder(&listOfBooks, book);
		}
		if (noEnd == -1){
			printf("Data on  row  %i has inappropriate format\n", indexRowOfFile);
		}
		++indexRowOfFile;
	};
	SortBooks(ByAlphabetAthors, &listOfBooks);
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