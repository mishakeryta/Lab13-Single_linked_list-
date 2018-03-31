#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "BookInfo.h"
typedef struct Snode
{
	TbookInfo m_info;
	struct Snode *m_pNext;
}Snode;
//створю новий елемент, у динамічній пам'яті
Snode* CreateNew(TbookInfo data);
//вставляє data ,пред тим створивши елемент списку,у правильне місце(проти алфавіту);
int InsertNewInOrder(Snode** list, TbookInfo info);
//видаляє всі книши з кількістю сторінок менше 50 
int DeleteLess50Pages(Snode** list);
//пахує кількість вуздів списку
//знаходить у списку 5 найновіших кних,зберігає їх у динамічному масиві, вказівник на який повертає
TbookInfo* FindTop5Latest(const Snode* list);
//видаляє список
int DeleteList(Snode** list);
//сортує книги за заданою умовою, повертає один, якщо все вдалося
//умови(способи) сортування
void PrintListBooks(const Snode* booksNode);
int  PrintListBooksToFile(const Snode* list, const char* szPath);
int DeleteHead(Snode** ppHeadOfList);
int CountNodes(const Snode* pList);

#endif
