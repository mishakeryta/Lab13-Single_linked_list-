#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookList.h"
//����� ������ �� ���������� ����
static int(*CmpModeOfSort)(const BookInfo* first, const BookInfo* second) = NotByAlphabetAuthors;

int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second))
{
	if (!cmpModeOfSort) return 0;
	CmpModeOfSort = CmpModeOfSort;
	return 1;
}
//������ ����� �������, � �������� ���'��
Node* CreateNew(BookInfo data) {
	Node* newElement = (Node*)malloc(sizeof(Node));
	newElement->info = data;
	newElement->next = NULL;
	return newElement;
}

//�������� ������ �� ���� ������� �������� list
int InsertToBegin(Node** list, Node* node) {
	if (!list) return 0;
	//�������� ������, ����� �� ������ ������
	node->next = *list;
	//�������� ������ ������ ����� �� ������
	(*list) = node;
	return 1;
}

//�������� data ,���� ��� ��������� ������� ������,� ��������� ����(����� �������);
int InsertNewInOrder(Node** list, BookInfo data) {
	if (!list) return 0;
	//������� ������� ������
	Node* newNode = CreateNew(data);
	//���� ������ ������ , ��� ����� ������� ����� ����� � �������� �� ������ 
	if (!*list || CmpModeOfSort(&(*list)->info, &newNode->info)) {
		//�������� �� ������� ������
		InsertToBegin(list, newNode);
		return 1;
	}
	//������ ���� ������ �� ������
	Node* crawler = *list;
	//���� � ��������, � ��� ��������� �����, �� ...
	while (crawler->next && !CmpModeOfSort(&crawler->next->info, &newNode->info)) {
		//��� ���
		crawler = crawler->next;
	}
	//���� ����� �� ����� �������������� ����
	if (!crawler->next) {
		crawler->next = newNode;
	}
	else {
		//������ �������� ������ ���������
		InsertToBegin(&crawler->next, newNode);
	}
	return 1;
}

//������� ��� ���� ������ ������ � ���������, ��� �� ���� �������� ������������
int SwapFirstAndNext(Node** head) {
	if (!head || !(*head) || !(*head)->next) return 0;
	Node* tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = *head;
	*head = tmp;
	return 1;
}
//������ ������ ����������
int ByAlphabetAuthors(const BookInfo* first, const BookInfo* second) {
	return (strcmp(first->author, second->author) <= 0) ? 0 : 1;
}
int NotByAlphabetAuthors(const BookInfo* first, const BookInfo* second) {
	return (strcmp(first->author, second->author) >= 0) ? 0 : 1;
}
int ByAlphabetName(const BookInfo* first, const BookInfo* second) {
	return (strcmp(first->name, second->name) <= 0) ? 0 : 1;
}
int NotByAlphabetName(const BookInfo* first, const BookInfo* second){
	return (strcmp(first->name, second->name) >= 0) ? 0 : 1;
}
int ByIncreasingPrice(const BookInfo* first, const BookInfo* second) {
	return first->price > second->price;
}
int ByReducingPrice(const BookInfo* first, const BookInfo* second) {
	return first->price < second->price;
}
int ByIncreasingYear(const BookInfo* first, const BookInfo* second) {
	return first->year > second->year;
}
int ByReducingYear(const BookInfo* first, const BookInfo* second) {
	return first->year < second->year;
}
int ByIncreasingPages(const BookInfo* first, const BookInfo* second) {
	return first->pages > second->pages;
}
int ByReducingPages(const BookInfo* first, const BookInfo* second) {
	return first->pages < second->pages;
}

//���� ����������.�� ������ �������� ��������  ���������
int SortBooks(Node** list) {
	if (!list || !*list || !(*list)->next) return 0;
	Node* crawler = 0;
	for (int i = 0, numberOfNodes = CountNodes(*list); i < numberOfNodes - 1; ++i) {
		if (CmpModeOfSort(&(*list)->info, &(*list)->next->info)) {
			SwapFirstAndNext(list);
		}
		crawler = *list;
		for (int j = 0; j < numberOfNodes - i - 2; ++j) {

			if (CmpModeOfSort(&crawler->next->info, &crawler->next->next->info)) {
				SwapFirstAndNext(&crawler->next);
			}
			crawler = crawler->next;
		}
	}
	return 1;
}

//������� ,��� ������� ����� , ���� ����������� �� ������� index 
Node* GetNode(Node* list, int index) {
	int i = 0;
	while (list) {
		if (i == index) break;
		++i;
		list = list->next;
	}
	return list;
}

//������� ������� � ������ �� ����� �� �����  ����� �� 50 ������� 
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
	Node *bookCrawler = (*booksNode) ? (*booksNode)->next : (*booksNode);
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
//���� ������� ����� � ������
int CountNodes(const Node* list) {
	int count = 0;
	while (list) {
		list = list->next;
		++count;
	}
	return count;
}
//������ ����� �� ������ 5 ��������� ����
BookInfo* FindTop5Latest(const Node* list) {
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
//������� ������
int DeleteList(Node **list) {
	if (!list) return 0;
	Node* tmp = NULL;
	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	return 1;
}

//�������� ����� ������ � �����
int InsertNewListFromFile(Node** list, char* path) {
	if (!list || path) return 0;
	BookInfo book = { 0 };
	FILE* inptr = fopen(path, "r");
	if (!inptr) {
		printf("Wrong path.");
		return 0;
	}
	int noEnd = 0;
	int indexRowOfFile = 1;
	while (noEnd = FReadBookInfo(&book, inptr)) {
		if (noEnd == 1) {
			if (!InsertNewInOrder(list, book)) return 0;
		}
		if (noEnd == -1) {
			printf("Data on  row  %i has inappropriate format\n", indexRowOfFile);
		}
		++indexRowOfFile;
	};
	fclose(inptr);
	return 1;
}