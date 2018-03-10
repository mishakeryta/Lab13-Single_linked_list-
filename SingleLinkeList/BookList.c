#define _CRT_SECURE_NO_WARNINGS


#include "BookList.h"
//режим встаки та сортування книг
static int(*CmpModeOfSort)(const BookInfo* first, const BookInfo* second) = NotByAlphabetAuthors;

int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second))
{
	if (!cmpModeOfSort) return 0;
	CmpModeOfSort = cmpModeOfSort;
	return 1;
}
//створю новий елемент, у динамічній пам'яті
Node* CreateNew(BookInfo data) {
	Node* newElement = (Node*)malloc(sizeof(Node));
	newElement->info = data;
	newElement->next = NULL;
	return newElement;
}

//вставляє елемен на місце першого елемента list
int InsertToBegin(Node** list, Node* node) {
	if (!list) return 0;
	//наступни нового, вказує на почаок списку
	node->next = *list;
	//вказівник голови списку вказує на нового
	(*list) = node;
	return 1;
}

//провіпряє чи така книга уже є в  списку
int IsBookInList(const Node* list, BookInfo info) {
	while (list) {
		if (IsBooksEqual(list->info, info)) return 1;
		list = list->next;
	}
	return 0;
}

//вставляє data ,пред тим створивши елемент списку,у правильне місце(проти алфавіту);
int InsertNewInOrder(Node** list, BookInfo info) {
	if (!list) return 0;
	if (IsBookInList(*list, info)) return -1;
	//створює елемент списку
	Node* newNode = CreateNew(info);
	//якщо список пустий , або новий елемент стоїть пізніше з алфавітом ніж перший 
	if (!*list || CmpModeOfSort(&(*list)->info, &newNode->info)) {
		//вставити на початок списку
		InsertToBegin(list, newNode);
		return 1;
	}
	//повзун який пробігає по списку
	Node* crawler = *list;
	//поки є наступни, і цей наступний пізніше, то ...
	while (crawler->next && !CmpModeOfSort(&crawler->next->info, &newNode->info)) {
		//йти далі
		crawler = crawler->next;
	}
	//якщо кінець то новий встановлюється туди
	if (!crawler->next) {
		crawler->next = newNode;
	}
	else {
		//інакше вставити замість останього
		InsertToBegin(&crawler->next, newNode);
	}
	return 1;
}

//функція яка міняє містями перший з наступним, але не міняє вказівник попереднього
int SwapFirstAndNext(Node** head) {
	if (!head || !(*head) || !(*head)->next) return 0;
	Node* tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = *head;
	*head = tmp;
	return 1;
}
//режими роботи сортування
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

//саме сортування.За основу береться алгоритм  бульбашки
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

//функція ,яка повертає вузол , який знаходиться на позиції index 
Node* GetNode(Node* list, int index) {
	int i = 0;
	while (list) {
		if (i == index) break;
		++i;
		list = list->next;
	}
	return list;
}

//функція яка видаляє переданий елемент, але нічоно не робить з вказівником попереднього
int DeleteHead(Node** head) {
	Node* tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

//Функція видаляє зі списку всі книги які мають  менше за 50 сторінок 
int DeleteLess50Pages(Node **booksNode)
{
	if (!(*booksNode)) {
		return 0;
	}
	Node *tmp = *booksNode;
	while (*booksNode && (*booksNode)->info.pages <= 50) {
		DeleteHead(booksNode);
	}
	if (!*booksNode || !(*booksNode)->next) return 1;
	Node* bookCrawler = *booksNode;
	while (bookCrawler->next) {
		if (bookCrawler->next->info.pages <= 50) {
			DeleteHead(&bookCrawler->next);
		}
	}
	return 1;
}
//рахує кількість вузлів у списку
int CountNodes(const Node* list) {
	int count = 0;
	while (list) {
		list = list->next;
		++count;
	}
	return count;
}
//створю масив що містить 5 найновіших книг
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
//видаляє список
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
//створити новий список з файлу
int InsertNewListFromFile(Node** list, const char* path) {
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
			case -1: printf("Element on row %i is allready in the list\n" ,indexRowOfFile); break;
			}
		}
		if (noEnd == -1) {
			printf("Element on  row  %i has inappropriate format \n", indexRowOfFile);
		}
		++indexRowOfFile;
	};

	return 1;
}

int DeleteBooks(Node** list, int index) {
	if (!list || !*list || index < 0) return 0;
	Node* tmp;
	if (index == 0) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		return 1;
	}
	for (int i = 0; i < index; ++i) {

	}
}