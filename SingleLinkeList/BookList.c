#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookList.h"
/*Функція яка копіює всі символи, доки не знайде символ endOfSource
*повертає 1 якщо вона знайшла символ, і у str вмстачило розміру
*check функція ,яка є умовою проходу символу*/
//провіряє чи символ може міститися у імені автора
inline int IsAuthorChar(int chr) {
	return isalpha(chr) || isblank(chr) || chr == '-';
}
//провіряє чи символ може міститися у назві книги
inline int IsNameBookChar(int chr) {
	return  IsAuthorChar(chr) || isdigit(chr);
}
//провіряє чи символ може міститися у цифрі з плавючою комою
inline int IsFloatDiginChar(int chr) {
	return isdigit(chr) || chr == '.';
}

//видаляж всі символи сhr , що входять у стрічку
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
//функція яка забирає лишні пробіли,та провіряє наявність тири підряд, або  пред іменем
int FormatAuthor(char* name) {
	int wasAlpha = 0;
	int blankZoneHaveDash = 0;
	if (isalpha(name[0])) wasAlpha = 1;
	if (name[0] == '-') return 0;
	//+ це символ , що буде видалений ці стрічки
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

//Функція яка провіряє рядок на наявність двох ком, або більше 2 цифер після коми
int CheckPriceFormatIsTrue(char* price) {
	if (!price) return 0;
	//кількість крапок , кількість цифр після крапки
	int numDot = 0, numDigitsAfterDot = 0;
	//цикл, який  проходтиться по рядку
	for (int i = 0, length = strlen(price); i < length; ++i) {
		//якщо була крапка збільшити кількість цифр після неї
		if (numDot) ++numDigitsAfterDot;
		//якщо крапка, збільшити кількість крапок
		if (price[i] == '.') ++numDot;
		//якщо це не число і не крапка або цількість крапок білше за одну  або кільк. циф після крап. білше за 2
		if (!(isdigit(price[i]) || price[i] == '.') || numDot >= 2 || numDigitsAfterDot > 2) return 0;
	}
	return 1;
}

//функція,яка зчитує дані з потуку(будьякого, навіть стандартного) 
int FReadBookInfo(BookInfo* info, FILE* inptr) {
	//перевірка, чи було предано NULL вказівник 
	if (!info || !inptr) return 0;
	//буфер для збергання рядку з даними
	char buffer[BUFFER_SIZE] = { 0 };
	//зчитування з потоку даних
	if (!fgets(buffer, BUFFER_SIZE - 1, inptr)) return 0;
	//змінна, яка зберігає позицію в буфері
	int indexOfBuffer = 0;
	//копіювання з буферу імені автора, якщо щось пішло не так, повернути -1, що означає помилку форматування
	if (!(indexOfBuffer = GetStrTo(info->author, SIZE_NAMES, '|', IsAuthorChar, buffer))) return -1;
	//перевірка формату імені, видалення лишніх пробілів, якщо формат не правильний, якщо щось пішло не так ...
	if (!FormatAuthor(info->author)) return -1;
	//пропуск риски в буфері
	++indexOfBuffer;

	//добавлення  з мінної яка зберігає зміщення позиції буферу в функції
	int indexLocalBuffer = 0;
	//зчитування імені книги з буферу(теперішньої позиції),зберігання зміщення 
	if (!(indexLocalBuffer = GetStrTo(info->name, SIZE_NAMES, '|', IsNameBookChar, buffer + indexOfBuffer))) return -1;
	//прехід на настувну позицію
	indexOfBuffer += indexLocalBuffer + 1;

	//стрічка(масив сисволив) ,яка зберігає стрічкове представлення року,кількості сторінок,ціни
	char tmpForDigits[12] = { 0 };
	//видалення всіх пробілів які йдуть після нашої позиції в буфері
	DeleteAll(' ', buffer + indexOfBuffer);
	//зчитування стрічкового представлення року видвння книги з буферу(теперішньої позиції),зберігання зміщення 
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	//перехід на нову позію 
	indexOfBuffer += indexLocalBuffer + 1;
	//конвертування та збереження року
	info->year = atoi(tmpForDigits);

	//те саме  з сторінками
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	indexOfBuffer += indexLocalBuffer + 1;
	info->pages = atoi(tmpForDigits);
	if (info->pages <= 0) return -1;

	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '\n', IsFloatDiginChar, buffer + indexOfBuffer))) return -1;
	// превірка формату ціни
	if (!CheckPriceFormatIsTrue(tmpForDigits)) return -1;
	info->price = atof(tmpForDigits);

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
//вставляє data ,пред тим створивши елемент списку,у правильне місце(проти алфавіту);
int InsertNewInOrder(Node** list, BookInfo data) {
	if (!list) return 0;
	//створює елемент списку
	Node* newNode = CreateNew(data);
	//якщо список пустий , або новий елемент стоїть пізніше з алфавітом ніж перший 
	if (!*list || strcmp((*list)->info.author, newNode->info.author) <= 0) {
		//вставити на початок списку
		InsertToBegin(list, newNode);
		return 1;
	}
	//повзун який пробігає по списку
	Node* crawler = *list;
	//поки є наступни, і цей наступний пізніше, то ...
	while (crawler->next && strcmp(crawler->next->info.author, newNode->info.author) >= 0) {
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


//функція яка міняє містями перший з наступним, але не міняє вказівник на попередній 
int SwapFirstAndNext(Node** head) {
	if (!head || !(*head) || !(*head)->next) return 0;
	Node* tmp = (*head)->next;
	(*head)->next = tmp->next;
	tmp->next = *head;
	*head = tmp;
	return 1;
}
//режими роботи сортування
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


//Функція видаляє зі списку всі книги які мають  менше за 50 сторінок 
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
//рахує кількість вузлів у списку
int CountNodes(const Node* list) {
	int count = 0;
	while (list) {
		list = list->next;
		++count;
	}
	return count;
}
//створю масив що містить 5 най новіших книг
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
void DeleteList(Node **list) {
	Node* tmp = NULL;
	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}