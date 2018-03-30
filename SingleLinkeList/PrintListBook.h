#ifndef PRINT_LIST_BOOK_HEADER
#define PRINT_LIST_BOOK_HEADER

#include "BookList.h"

void PrintTemplate(void);
void PrintBookInfo(BookInfo data);
void PrintListBooks(const Snode* booksNode);
int  PrintListBooksToFile(const Snode* list, const char* path);
void PrintArrayBooks(const BookInfo* arrBooksInfo, int num);
#endif
