#define _CRT_SECURE_NO_WARNINGS
#include "BookList.h"
Snode* CreateNew(TbookInfo data) {
	Snode* newElement = (Snode*)malloc(sizeof(Snode));
	newElement->m_info = data;
	newElement->m_pNext = NULL;
	return newElement;
}
int InsertToBegin(Snode** list, Snode* node) {
	if (!list) return 0;
	node->m_pNext = *list;
	(*list) = node;
	return 1;
}
int IsBookInList(const Snode* list, TbookInfo info) {
	while (list) {
		if (IsBooksEqual(list->m_info, info)) return 1;
		list = list->m_pNext;
	}
	return 0;
}
int InsertNewInOrder(Snode** list, TbookInfo data) {
	if (!list) return 0;
	Snode* newNode = CreateNew(data);
	if (!(*list)) {
		*list = newNode;
		return 1;
	}
	if (strcmp((*list)->m_info.author, newNode->m_info.author) <= 0) {
		InsertToBegin(list, newNode);
		return 1;
	}
	Snode* crawler = *list;
	while (crawler->m_pNext && strcmp(crawler->m_pNext->m_info.author, newNode->m_info.author) >= 0) {
		crawler = crawler->m_pNext;
	}
	if (!crawler->m_pNext) {
		crawler->m_pNext = newNode;
	}
	else {
		InsertToBegin(&crawler->m_pNext, newNode);
	}
	return 1;
}
//функція яка видаляє переданий елемент, але нічоно не робить з вказівником попереднього
int DeleteHead(Snode** head) {
	Snode* pTmp = *head;
	*head = (*head)->m_pNext;
	free(pTmp);
}
//Функція видаляє зі списку всі книги які мають  менше за 50 сторінок 
int DeleteLess50Pages(Snode **booksNode) {
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
		}else {
			bookCrawler = bookCrawler->m_pNext;
		}
	}
	return 1;
}

//створю масив що містить 5 найновіших книг
TbookInfo* FindTop5Latest(const Snode* list) {
	if (!list) return NULL;
	int countOfElements = CountNodes(list);
	if (countOfElements < 5)return NULL;
	char* isInNodeWithNum = (char*)calloc(countOfElements, sizeof(char));
	TbookInfo* top5Latest = (TbookInfo*)calloc(5, sizeof(TbookInfo));
	for (int i = 0; i < 5; ++i)
	{
		TbookInfo tmp = list->m_info;
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
//видаляє список
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
//створити новий список з файлу
void PrintListBooks(const Snode* booksNode) {
	if (!booksNode) {
		return;
	}
	PrintRows(5, 27, 25, 6, 5, 6);
	PrintTemplate();
	PrintRows(5, 27, 25, 6, 5, 6);
	do {
		PrintBook(booksNode->m_info);
		PrintRows(5, 27, 25, 6, 5, 6);
		booksNode = booksNode->m_pNext;
	} while (booksNode);
}

//вставляє вміст списку у файл(звісно вміст зюерігається у відповідному форматі)
//попередній вміст файлу стирається
int PrintListBooksToFile(const Snode* list, const char* path) {
	if (!path) return 0;
	//стираємо попередній вміст файлу
	FILE*  outptr = fopen(path, "w");
	if (!outptr)  return 0;
	fclose(outptr);
	outptr = fopen(path, "a");
	while (list) {
		PrintBookToFile(list->m_info, outptr);
		list = list->m_pNext;
	}
	fclose(outptr);
	return 1;
}
int CountNodes(const Snode* psList) {
	int nCount = 0;
	while (psList) {
		psList = psList->m_pNext;
		++nCount;
	}
	return nCount;
}
