#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookList.h"
/*������� ��� ����� �� �������, ���� �� ������ ������ endOfSource
*������� 1 ���� ���� ������� ������, � � str ��������� ������
*check ������� ,��� � ������ ������� �������*/
//������� �� ������ ���� �������� � ���� ������
inline int IsAuthorChar(int chr) {
	return isalpha(chr) || isblank(chr) || chr == '-';
}
//������� �� ������ ���� �������� � ���� �����
inline int IsNameBookChar(int chr) {
	return  IsAuthorChar(chr) || isdigit(chr);
}
//������� �� ������ ���� �������� � ���� � �������� �����
inline int IsFloatDiginChar(int chr) {
	return isdigit(chr) || chr == '.';
}

//������� �� ������� �hr , �� ������� � ������
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
//������� ��� ������ ���� ������,�� ������� �������� ���� �����, ���  ���� ������
int FormatAuthor(char* name) {
	int wasAlpha = 0;
	int blankZoneHaveDash = 0;
	if (isalpha(name[0])) wasAlpha = 1;
	if (name[0] == '-') return 0;
	//+ �� ������ , �� ���� ��������� �� ������
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

/*������� ��� ����� �� �������, ���� �� ������ ������ endOfSource
*������� 1 ���� ���� ������� ������, � � str ��������� ������
*check ������� ,��� � ������ ������� �������*/
int GetStrTo(char* dest, int sizeOfDest, char endOfSource, int(*check)(int), char* source) {
	if (!dest || !source || !check) return 0;
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

//������� ��� ������� ����� �� �������� ���� ���, ��� ����� 2 ����� ���� ����
int CheckPriceFormatIsTrue(char* price) {
	if (!price) return 0;
	//������� ������ , ������� ���� ���� ������
	int numDot = 0, numDigitsAfterDot = 0;
	//����, ����  ������������ �� �����
	for (int i = 0, length = strlen(price); i < length; ++i) {
		//���� ���� ������ �������� ������� ���� ���� ��
		if (numDot) ++numDigitsAfterDot;
		//���� ������, �������� ������� ������
		if (price[i] == '.') ++numDot;
		//���� �� �� ����� � �� ������ ��� �������� ������ ���� �� ����  ��� ����. ��� ���� ����. ���� �� 2
		if (!(isdigit(price[i]) || price[i] == '.') || numDot >= 2 || numDigitsAfterDot > 2) return 0;
	}
	return 1;
}

//�������,��� ����� ��� � ������(���������, ����� ������������) 
int FReadBookInfo(BookInfo* info, FILE* inptr) {
	//��������, �� ���� ������� NULL �������� 
	if (!info || !inptr) return 0;
	//����� ��� ��������� ����� � ������
	char buffer[BUFFER_SIZE] = { 0 };
	//���������� � ������ �����
	if (!fgets(buffer, BUFFER_SIZE - 1, inptr)) return 0;
	//�����, ��� ������ ������� � �����
	int indexOfBuffer = 0;
	//��������� � ������ ���� ������, ���� ���� ���� �� ���, ��������� -1, �� ������ ������� ������������
	if (!(indexOfBuffer = GetStrTo(info->author, SIZE_NAMES, '|', IsAuthorChar, buffer))) return -1;
	//�������� ������� ����, ��������� ����� ������, ���� ������ �� ����������, ���� ���� ���� �� ��� ...
	if (!FormatAuthor(info->author)) return -1;
	//������� ����� � �����
	++indexOfBuffer;

	//����������  � ���� ��� ������ ������� ������� ������ � �������
	int indexLocalBuffer = 0;
	//���������� ���� ����� � ������(��������� �������),��������� ������� 
	if (!(indexLocalBuffer = GetStrTo(info->name, SIZE_NAMES, '|', IsNameBookChar, buffer + indexOfBuffer))) return -1;
	//������ �� �������� �������
	indexOfBuffer += indexLocalBuffer + 1;

	//������(����� ��������) ,��� ������ �������� ������������� ����,������� �������,����
	char tmpForDigits[12] = { 0 };
	//��������� ��� ������ �� ����� ���� ���� ������� � �����
	DeleteAll(' ', buffer + indexOfBuffer);
	//���������� ���������� ������������� ���� ������� ����� � ������(��������� �������),��������� ������� 
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	//������� �� ���� ���� 
	indexOfBuffer += indexLocalBuffer + 1;
	//������������� �� ���������� ����
	info->year = atoi(tmpForDigits);

	//�� ����  � ���������
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	indexOfBuffer += indexLocalBuffer + 1;
	info->pages = atoi(tmpForDigits);
	if (info->pages <= 0) return -1;

	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '\n', IsFloatDiginChar, buffer + indexOfBuffer))) return -1;
	// ������� ������� ����
	if (!CheckPriceFormatIsTrue(tmpForDigits)) return -1;
	info->price = atof(tmpForDigits);

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
	if (!*list || strcmp((*list)->info.author, newNode->info.author) <= 0) {
		//�������� �� ������� ������
		InsertToBegin(list, newNode);
		return 1;
	}
	//������ ���� ������ �� ������
	Node* crawler = *list;
	//���� � ��������, � ��� ��������� �����, �� ...
	while (crawler->next && strcmp(crawler->next->info.author, newNode->info.author) >= 0) {
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


//������� ��� ���� ������ ������ � ���������, ��� �� ���� �������� �� ��������� 
int SwapFirstAndNext(Node** head) {
	if (!head || !(*head) || !(*head)->next) return 0;
	Node* tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = *head;
	*head = tmp;
	return 1;
}
//������ ������ ����������
inline int ByAlphabetAthors(const BookInfo* first, const BookInfo* second) {
	return (strcmp(first->author, second->author) <= 0) ? 0 : 1;
}
inline int NotByAlphabetAthors(const BookInfo* first, const BookInfo* second) {
	return (strcmp(first->author, second->author) >= 0) ? 0 : 1;
}
inline int ByIncreasingPrice(const BookInfo* first, const BookInfo* second) {
	return first->price>second->price;
}
inline int ByReducingPrice(const BookInfo* first, const BookInfo* second) {
	return first->price<second->price;
}
inline int ByIncreasingYear(const BookInfo* first, const BookInfo* second) {
	return first->year>second->year;
}
inline int ByReducingYear(const BookInfo* first, const BookInfo* second) {
	return first->year<second->year;
}
inline int ByIncreasingPages(const BookInfo* first, const BookInfo* second) {
	return first->price>second->price;
}
inline int ByReducingPages(const BookInfo* first, const BookInfo* second) {
	return first->price<second->price;
}

int SortBooks(int(*orderCmp)(const BookInfo*, const BookInfo*), Node** list) {
	if (!list || !*list || !(*list)->next || !orderCmp) return 0;
	Node* crawler = 0;
	for (int i = 0, numberOfNodes = CountNodes(*list); i < numberOfNodes; ++i) {
		for (int j = 0; j < numberOfNodes - i - 2; ++j) {
			if (!j) {
				if (orderCmp(&(*list)->info, &(*list)->next->info)) {
					SwapFirstAndNext(list);
				}
				crawler = *list;
			}
			if (orderCmp(&crawler->next->info, &crawler->next->next->info)) {
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
//������ ����� �� ������ 5 ��� ������ ����
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
void DeleteList(Node **list) {
	Node* tmp = NULL;
	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}