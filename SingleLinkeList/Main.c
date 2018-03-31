#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "BookList.h"
int main(void) {

	//сам список
	Snode* pList = NULL;

	//тимчасово зберігає дані зчитані з файлу Books.txt
	TbookInfo bookInfoTmp = { 0 };

	FILE* pfBooks = fopen("Books.txt", "r");
	if (!pfBooks) {
		printf("You dont have file Books.txt. \n");
	}

	//nChecker -зберігає значення, що повертає фунція, для виявлення даних не
	//правильного форматування
	int nChecker = 0, nRowInFile = 1;
	printf("Read books from file Books.txt\n");
	while (nChecker = ReadBookInfoFromFile(&bookInfoTmp, pfBooks)) {
		if (nChecker == -1) {
			printf("Data in file Books.txt on row %i has inappropriate format.\n", nRowInFile);
		}
		else {
			InsertNewInOrder(&pList, bookInfoTmp);
		}
		++nRowInFile;
	}
	PrintListBooks(pList);
	printf("Find top 5 latest books\n");
	TbookInfo* pTop5LatestBooks = FindTop5Latest(pList);
	if (!pTop5LatestBooks) {
		printf("List does not contain so many books.\n");
	}
	else
	{
		printf("Top 5 latest books:\n");
		PrintArrayBooks(pTop5LatestBooks, 5);
		free(pTop5LatestBooks);
	}
	printf("Delete books with less then 50 pages.\n");
	DeleteLess50Pages(&pList);
	PrintListBooks(pList);
	DeleteList(&pList);
	getchar(); getchar();
	return 0;

}
