#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookList.h"
/*Функція яка копіює всі символи, доки не знайде символ endOfSource
*повертає 1 якщо вона знайшла символ, і у str вмстачило розміру
*check функція ,яка є умовою проходу символу*/
inline int IsAuthorChar(int chr) {
	return isalpha(chr) || isblank(chr) || chr == '-';
}
inline int IsNameBookChar(int chr) {
	return  IsAuthorChar(chr) || isdigit(chr);
}
inline int IsFloatDiginChar(int chr) {
	return isdigit(chr) || chr == '.';
}

int DeleteAll(char chr, char*str) {
	if (!str) return 0;
	for (int i = 0, length = strlen(str); i < length; ++i) {
		if (str[i] == chr) {
			int start = i;
			do {
				++i;
			} while (str[i] == chr);
			strcpy(str + start, str + i);
			i = start;
		}
	}
	return 1;
}
int FormatAuthor(char* name) {
	int wasAlpha = 0;
	int blankZoneHaveDash = 0;
	if (isalpha(name[0])) wasAlpha = 1;
	if (name[0] == '-') return 0;
	if (name[0] == ' ') name[0] = '+';

	for (int i = 1, length = strlen(name); i < length; ++i) {
		if (name[i] == '-') {
			if (!wasAlpha || blankZoneHaveDash) { return 0; }
			else {
				blankZoneHaveDash = 1;
			}
			if (name[i - 1] == ' ') {
				name[i - 1] = '+';
			}
		}
		if (isblank(name[i])) {
			if (name[i - 1] == ' ' || name[i - 1] == '+') {
				name[i] = '+';
			}
		}
		if (isalpha(name[i])) {
			wasAlpha = 1;
			blankZoneHaveDash = 0;
		}
	}
	if (!DeleteAll('+', name)) return 0;
	return 1;
}

/*Функція яка копіює всі символи, доки не знайде символ endOfSource
*повертає 1 якщо вона знайшла символ, і у str вмстачило розміру
*check функція ,яка є умовою проходу символу*/
int GetStrTo(char* dest, int sizeOfDest, char endOfSource, int(*check)(int), char* source) {
	for (int i = 0; i < sizeOfDest; ++i) {

		if (source[i] == endOfSource) {
			dest[i] = 0;
			return i;
		}
		if (!check(source[i])) return 0;
		dest[i] = source[i];
	}
	return 0;
}

//Функція яка провіряє рядок на наявність двох ком, або більше 2 цифер після коми
int CheckPriceFormatIsTrue(char* price) {
	if (!price) return 0;
	int numDot = 0;
	for (int i = 0, length = strlen(price); i < length; ++i) {
		if (price[i] == '.') ++numDot;
		if (!(isdigit(price[i]) || price[i] == '.') || numDot >= 2) return 0;
	}
	return 1;
}

//фенкція ,яка зчитує дані з клавіатури
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
//функція,яка зчитує дані з потуку(будьякого, навіть стандартного) 
int FReadBookInfo(BookInfo* info, FILE* inptr) {
	if (!info || !inptr) return 0;
	char buffer[BUFFER_SIZE] = { 0 };
	if (!fgets(buffer, BUFFER_SIZE - 1, inptr)) return 0;

	int indexOfBuffer = 0;
	if (!(indexOfBuffer = GetStrTo(info->author, SIZE_NAMES, '|', IsAuthorChar, buffer))) return -1;
	++indexOfBuffer;
	if (!FormatAuthor(info->author)) return -1;

	int indexLocalBuffer = 0;
	if (!(indexLocalBuffer = GetStrTo(info->name, SIZE_NAMES, '|', IsNameBookChar, buffer + indexOfBuffer))) return -1;
	indexOfBuffer += indexLocalBuffer + 1;

	char tmpForDigits[12] = { 0 };
	DeleteAll(' ', buffer + indexOfBuffer);
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	indexOfBuffer += indexLocalBuffer + 1;
	info->year = atoi(tmpForDigits);

	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	indexOfBuffer += indexLocalBuffer + 1;
	info->pages = atoi(tmpForDigits);
	if (info->pages <= 0) return -1;

	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '\n', IsFloatDiginChar, buffer + indexOfBuffer))) return -1;
	if (!CheckPriceFormatIsTrue(tmpForDigits)) return -1;
	info->price = atof(tmpForDigits);

	return 1;
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
int InsertNewInOrder(Node** list, BookInfo data) {
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
//...
void DeleteList(Node **list) {
	Node* tmp = NULL;
	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}