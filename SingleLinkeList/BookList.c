#define _CRT_SECURE_NO_WARNINGS


#include "BookList.h"
//����� ������ �� ���������� ����
static int(*CmpModeOfSort)(const BookInfo* first, const BookInfo* second) = NotByAlphabetAuthors;

int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second))
{
	if (!cmpModeOfSort) return 0;
	CmpModeOfSort = cmpModeOfSort;
	return 1;
}
//������ ����� �������, � �������� ���'��
Snode* CreateNew(BookInfo data) {
	Snode* newElement = (Snode*)malloc(sizeof(Snode));
	newElement->m_info = data;
	newElement->m_pNext = NULL;
	return newElement;
}

//�������� ������ �� ���� ������� �������� list
int InsertToBegin(Snode** list, Snode* node) {
	if (!list) return 0;
	//�������� ������, ����� �� ������ ������
	node->m_pNext = *list;
	//�������� ������ ������ ����� �� ������
	(*list) = node;
	return 1;
}

//�������� �� ���� ����� ��� � �  ������
int IsBookInList(const Snode* list, BookInfo info) {
	while (list) {
		if (IsBooksEqual(list->m_info, info)) return 1;
		list = list->m_pNext;
	}
	return 0;
}
//�������� data ,���� ��� ��������� ������� ������,� ��������� ����(����� �������);
int InsertNewInOrder(Snode** list, BookInfo info) {
	if (!list) return 0;
	if (IsBookInList(*list, info)) return -1;
	//������� ������� ������
	Snode* newNode = CreateNew(info);
	//���� ������ ������ , ��� ����� ������� ����� ����� � �������� �� ������ 
	if (!*list || CmpModeOfSort(&(*list)->m_info, &newNode->m_info)) {
		//�������� �� ������� ������
		InsertToBegin(list, newNode);
		return 1;
	}
	//������ ���� ������ �� ������
	Snode* crawler = *list;
	//���� � ��������, � ��� ��������� �����, �� ...
	while (crawler->m_pNext && !CmpModeOfSort(&crawler->m_pNext->m_info, &newNode->m_info)) {
		//��� ���
		crawler = crawler->m_pNext;
	}
	//���� ����� �� ����� �������������� ����
	if (!crawler->m_pNext) {
		crawler->m_pNext = newNode;
	}
	else {
		//������ �������� ������ ���������
		InsertToBegin(&crawler->m_pNext, newNode);
	}
	return 1;
}

//������� ��� ���� ������ ������ � ���������, ��� �� ���� �������� ������������
int SwapFirstAndNext(Snode** head) {
	if (!head || !(*head) || !(*head)->m_pNext) return 0;
	Snode* tmp = (*head)->m_pNext;
	(*head)->m_pNext = tmp->m_pNext;
	tmp->m_pNext = *head;
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
int NotByAlphabetName(const BookInfo* first, const BookInfo* second) {
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
int SortBooks(Snode** list) {
	if (!list || !*list || !(*list)->m_pNext) return 0;
	Snode* crawler = 0;
	for (int i = 0, numberOfNodes = CountNodes(*list); i < numberOfNodes - 1; ++i) {
		if (CmpModeOfSort(&(*list)->m_info, &(*list)->m_pNext->m_info)) {
			SwapFirstAndNext(list);
		}
		crawler = *list;
		for (int j = 0; j < numberOfNodes - i - 2; ++j) {
			if (CmpModeOfSort(&crawler->m_pNext->m_info, &crawler->m_pNext->m_pNext->m_info)) {
				SwapFirstAndNext(&crawler->m_pNext);
			}
			crawler = crawler->m_pNext;
		}
	}
	return 1;
}

//������� ,��� ������� ����� , ���� ����������� �� ������� index 
Snode* GetNode(Snode* list, int index) {
	int i = 0;
	while (list) {
		if (i == index) break;
		++i;
		list = list->m_pNext;
	}
	return list;
}

//������� ��� ������� ��������� �������, ��� ����� �� ������ � ���������� ������������
int DeleteHead(Snode** head) {
	Snode* tmp = *head;
	*head = (*head)->m_pNext;
	free(tmp);
}

//������� ������� � ������ �� ����� �� �����  ����� �� 50 ������� 
int DeleteLess50Pages(Snode **booksNode)
{
	if (!(*booksNode)) {
		return 0;
	}
	Snode *tmp = *booksNode;
	while (*booksNode && (*booksNode)->m_info.pages <= 50) {
		DeleteHead(booksNode);
	}
	if (!*booksNode || !(*booksNode)->m_pNext) return 1;
	Snode* bookCrawler = *booksNode;
	while (bookCrawler->m_pNext) {
		if (bookCrawler->m_pNext->m_info.pages <= 50) {
			DeleteHead(&bookCrawler->m_pNext);
		}
	}
	return 1;
}
//���� ������� ����� � ������
int CountNodes(const Snode* list) {
	int count = 0;
	while (list) {
		list = list->m_pNext;
		++count;
	}
	return count;
}
//������ ����� �� ������ 5 ��������� ����
BookInfo* FindTop5Latest(const Snode* list) {
	if (!list) return NULL;
	int countOfElements = CountNodes(list);
	if (countOfElements < 5)return NULL;
	char* isInNodeWithNum = (char*)calloc(countOfElements, sizeof(char));
	BookInfo* top5Latest = (BookInfo*)calloc(5, sizeof(BookInfo));
	for (int i = 0; i < 5; ++i)
	{
		BookInfo tmp = list->m_info;
		const Snode* crawler = list;
		int numOfNode = 0;
		int goingInNode = 0;
		while (crawler)
		{
			if (crawler->m_info.year >= tmp.year && !isInNodeWithNum[numOfNode])
			{
				tmp = crawler->m_info;
				goingInNode = numOfNode;
			}
			++numOfNode;
			crawler = crawler->m_pNext;
		}
		top5Latest[i] = tmp;
		isInNodeWithNum[goingInNode] = 1;
	}
	return top5Latest;
}
//������� ������
int DeleteList(Snode **list) {
	if (!list) return 0;
	Snode* tmp = NULL;
	while (*list) {
		tmp = *list;
		*list = (*list)->m_pNext;
		free(tmp);
	}
	return 1;
}
//�������� ����� ������ � �����
int InsertNewListFromFile(Snode** list, const char* path) {
	if (!list || !path) return 0;
	BookInfo book = { 0 };
	FILE* inptr = fopen(path, "r");
	if (!inptr) {
		printf("Wrong path\n");
		return 0;
	}
	int noEnd = 0;
	int indexRowOfFile = 1;
	while (noEnd = FReadBookInfo(&book, inptr)) {
		if (noEnd == 1) {
			switch (InsertNewInOrder(list, book))
			{
			case 0: { fclose(inptr); return 0; }
			case -1: printf("Element on row %i is allready in the list\n", indexRowOfFile); break;
			}
		}
		else {
			printf("Element on  row  %i has inappropriate format \n", indexRowOfFile);
		}
		++indexRowOfFile;
	};

	return 1;
}
int DeleteBooks(Snode** list, int index) {
	if (!list || !*list || index < 0) return 0;
	Snode* tmp;
	if (index == 0) {
		tmp = *list;
		*list = (*list)->m_pNext;
		free(tmp);
		return 1;
	}
	for (int i = 0; i < index; ++i) {

	}
}