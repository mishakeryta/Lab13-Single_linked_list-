#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BookList.h"

//function thet read data
BookInfo ReadBookInfo() {
	BookInfo  data = { 0 };
	printf("Enter name of author:");
	fgets(data.author, SIZE_NAMES, stdin);
	data.author[strlen(data.author) - 1] = 0;
	printf("Enter name of book:");
	fgets(data.name, SIZE_NAMES, stdin);
	data.author[strlen(data.author) - 1] = 0;
	printf("Enter year,number of page and price of the book:\n");
	scanf("%i %i %lf", &data.year, &data.pages, &data.price);
	return data;
}
BookInfo FReadBookInfo(FILE* fStream) {
	BookInfo data = { 0 };
	do {
		if (fgets(data.author, SIZE_NAMES, fStream) == NULL) {
			break;
		}
		data.author[strlen(data.author) - 1] = 0;
		if (fgets(data.name, SIZE_NAMES, fStream) == NULL) {
			break;
		}
		data.name[strlen(data.name) - 1] = 0;
		char szTmp[10] = { 0 };
		if (fgets(szTmp, 10, fStream) == NULL) {
			break;
		}
		data.year = atoi(szTmp);

		if (fgets(szTmp, 10, fStream) == NULL) {
			break;
		}
		data.pages = atoi(szTmp);
		if (fgets(szTmp, 10, fStream) == NULL) {
			break;
		}
		data.price = atof(szTmp);
	} while (0);
	return data;
}

Node* CreateNew(BookInfo data) {
	Node* newElement = (Node*)malloc(sizeof(Node));
	newElement->info = data;
	newElement->next = NULL;
	return newElement;
}
//inset to begin some node
int InsertToBegin(Node** list, Node* node) {
	if (!list) return 0;
	node->next = *list;
	(*list) = node;
	return 1;
}
//Insert against the alphabet
int InsetNewInOrder(Node** list, BookInfo data) {
	if (!list) return 0;
	Node* newNode = CreateNew(data);
	if (!(*list)) {
		*list = newNode;
		return 1;
	}
	if (strcmp((*list)->info.author, newNode->info.author) <= 0) {
		InsertToBegin(list, newNode);
		return 1;
	}
	Node* crawler = *list;
	while (crawler->next && strcmp(crawler->next->info.author, newNode->info.author) >= 0) {
		crawler = crawler->next;
	}
	if (!crawler->next) {
		crawler->next = newNode;
	}
	else {
		InsertToBegin(&crawler->next, newNode);
	}
	return 1;
}
//...
int DeleteLess50Pages(Node **booksNode)
{
	if (!(*booksNode)) {
		return 0;
	}
	Node *tmp = *booksNode;
	while ((*booksNode)->info.pages <= 50 && *booksNode) {
		tmp = *booksNode;
		*booksNode = (*booksNode)->next;
		free(tmp);
	}
	Node *bookCrawler = (*booksNode) ? (*booksNode)->next:(*booksNode);
	while (bookCrawler) {
		if (bookCrawler->info.pages <= 50) {
			tmp->next = bookCrawler->next;
			free(bookCrawler);
			bookCrawler = tmp;
		}
		tmp = bookCrawler;
		bookCrawler = bookCrawler->next;
	}
	return 1;
}
//count num of nodes
int CountNodes(const Node* list) {
	int count = 0;
	while (list) {
		list = list->next;
		++count;
	}
	return count;
}
//create array with top 5 latest books in list 
BookInfo* FindTop5Latest(const Node* list){
	if (!list) return NULL;
	int countOfElements = CountNodes(list);
	if (countOfElements < 5)return NULL;
	char* isInNodeWithNum = (char*)calloc(countOfElements, sizeof(char));
	BookInfo* top5Latest = (BookInfo*)calloc(5, sizeof(BookInfo));
	for (int i = 0; i < 5; ++i)
	{
		BookInfo tmp = list->info;
		const Node* crawler = list;
		int numOfNode = 0;
		int goingInNode = 0;
		while (crawler)
		{
			if (crawler->info.year >= tmp.year && !isInNodeWithNum[numOfNode])
			{
				tmp = crawler->info;
				goingInNode = numOfNode;
			}
			++numOfNode;
			crawler = crawler->next;
		}
		top5Latest[i] = tmp;
		isInNodeWithNum[goingInNode] = 1;
	}
	return top5Latest;
}
//...
void DeleteList(Node **list){
	Node* tmp = NULL;
	while (*list){
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	*list = NULL;
}