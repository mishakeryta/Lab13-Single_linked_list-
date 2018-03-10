#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "BookList.h"


#define MAIN_STR "<<BookInfo>>\n\
Plese eter button:\n\
1-Add new(format:Author(max length 70)|Name (max length 70)|year|num of pages| price (press enter),\n\
2-Add from Books.txt\n\
3-Save changes to Books.txt\n\
4-Sort\n\
5-Show\n\
6-Find5Latest\n\
7-Delete list\n\
8-Exit\n"
#define SORT_METHODS_STR "Sort book in order(press key):\n\
1 - by alphabet authors\n\
2 - against alphabet athors\n\
3 - by alphabet authors\n\
4 - against alphabet athors\n\
5 - by increasing price\n\
6 - by reducing price\n\
7 - by increasing year\n\
8 - by reducing year\n\
9 - by increasing pages\n\
0 - by reducing pages\n\
Any - return|\n"

int main(void) {
	Node* bookList = NULL;
	BookInfo tmpInfo = { 0 };
	printf(MAIN_STR);
	char control = 0;
	BookInfo* top5Latest = NULL;
	while ((control = _getche()) != 8) {
		system("cls");
		switch (control)
		{
		case'1':
			printf("Plese enter new element in so format:\n\
Author(max length 70)|Name (max length 70)|year|num of pages| price (press enter),\n");
			switch (FReadBookInfo(&tmpInfo, stdin))
			{
			case 0:printf("Fail\n"); break;
			case 1:printf("Aprropriate format\n");
				if (InsertNewInOrder(&bookList, tmpInfo)) {
					printf("Adding successful\n");
				}
				else {
					printf("Fail\n");
				}
				break;
			case -1:printf("Inaropriate fromat\n"); break;
			case -2:printf("Element is in the list\n"); break;
			}
			break;
		case'2':
			if (InsertNewListFromFile(&bookList, "Books.txt")) {
				printf("Adding sucsseful\n");
			}
			else {
				printf("Fail\n");
			}
			break;
		case'3':
			if (FPrintListBooks(bookList, "Books.txt")) {
				printf("Saving sucssesful\n");
			}
			else {
				printf("Fail\n");
			}
			break;
		case'4':
			system("cls");
			printf(SORT_METHODS_STR);

			switch (_getche()) {
			case '1':SetOrder(ByAlphabetAuthors); break;
			case '2':SetOrder(NotByAlphabetAuthors); break;
			case '3':SetOrder(ByAlphabetName); break;
			case '4':SetOrder(NotByAlphabetName); break;
			case '5':SetOrder(ByIncreasingPrice); break;
			case '6':SetOrder(ByReducingPrice); break;
			case '7':SetOrder(ByIncreasingYear); break;
			case '8':SetOrder(ByReducingYear); break;
			case '9':SetOrder(ByIncreasingPages); break;
			case '0':SetOrder(ByReducingPages); break;
			}
			if (SortBooks(&bookList)) {
				printf("Sorting  sucsseful\n");
			}
			else {
				printf("Fail\n");
			}
			break;
		case '5':PrintListBooks(bookList);
			printf("Printing sucsseful\n");
			break;
		case '6':
			if (top5Latest = FindTop5Latest(bookList)) {
				printf("Finding top 5 latest sucssesful\n");
				PrintArrayBooks(top5Latest, 5);
			}
			else {
				printf("Fail\n");
			}
			break;
		case '7':
			DeleteList(&bookList);
			break;
		case '8':
			return 0;

		}
		printf(MAIN_STR);
	}

	return 0;
}
