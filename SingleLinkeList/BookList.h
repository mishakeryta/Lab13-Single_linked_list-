#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER



#include "BookInfo.h"
typedef struct SNode
{
	BookInfo info;
	struct SNode *next;
}Node;

//створю новий елемент, у динамічній пам'яті
Node* CreateNew(BookInfo data);
//вставляє data ,пред тим створивши елемент списку,у правильне місце(проти алфавіту);
int InsertNewInOrder(Node** list, BookInfo data);
//видаляє всі книши з кількістю сторінок менше 50 
int DeleteLess50Pages(Node** list);
//пахує кількість вуздів списку
int CountNodes(const Node* list);
//знаходить у списку 5 найновіших кних,зберігає їх у динамічному масиві, вказівник на який повертає
BookInfo* FindTop5Latest(const Node* list);
//видаляє список
int DeleteList(Node** list);
Node* GetNode(Node* list, int index);

//сортує книги за заданою умовою, повертає один, якщо все вдалося
int SortBooks( Node** list);

//умови(способи) сортування
int ByAlphabetAuthors(const BookInfo* first, const BookInfo* second);

int NotByAlphabetAuthors(const BookInfo* first, const BookInfo* second);

int ByAlphabetName(const BookInfo* first, const BookInfo* second);

int NotByAlphabetName(const BookInfo* first, const BookInfo* second);
int ByIncreasingPrice(const BookInfo* first, const BookInfo* second);

int ByReducingPrice(const BookInfo* first, const BookInfo* second);

int ByIncreasingYear(const BookInfo* first, const BookInfo* second);

int ByReducingYear(const BookInfo* first, const BookInfo* second);

int ByIncreasingPages(const BookInfo* first, const BookInfo* second);

int ByReducingPages(const BookInfo* first, const BookInfo* second);
int InsertNewListFromFile(Node**list, char*path);


int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second));
#include "PrintListBook.h"
#endif
