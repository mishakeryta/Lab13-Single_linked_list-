#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookInfo.h"
typedef struct Snode
{
	BookInfo m_info;
	struct Snode *m_pNext;
}Snode;

//створю новий елемент, у динамічній пам'яті
Snode* CreateNew(BookInfo data);
//вставляє data ,пред тим створивши елемент списку,у правильне місце(проти алфавіту);
int InsertNewInOrder(Snode** list, BookInfo info);
//видаляє всі книши з кількістю сторінок менше 50 
int DeleteLess50Pages(Snode** list);
//пахує кількість вуздів списку
int CountNodes(const Snode* list);
//знаходить у списку 5 найновіших кних,зберігає їх у динамічному масиві, вказівник на який повертає
BookInfo* FindTop5Latest(const Snode* list);
//видаляє список
int DeleteList(Snode** list);
Snode* GetNode(Snode* list, int index);

//сортує книги за заданою умовою, повертає один, якщо все вдалося
int SortBooks(Snode** list);

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
int InsertNewListFromFile(Snode**list, const char*path);

int SetOrder(int(*cmpModeOfSort)(const BookInfo* first, const BookInfo* second));

int DeleteHead(Snode** head);
#include "PrintListBook.h"
#endif
