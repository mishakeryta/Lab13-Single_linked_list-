#ifndef BOOK_LIST_HEADER
#define BOOK_LIST_HEADER

#define SIZE_NAMES 71
typedef struct SBookInfo
{
	char author[SIZE_NAMES];
	char name[SIZE_NAMES];
	int year;
	int pages;
	double price;
}BookInfo;

typedef struct SNode
{
	BookInfo info;
	struct SNode *next;
}Node;

BookInfo ReadBookInfo();

//number of chars in one line of fStream
#define BUFFER_SIZE 1000
int FReadBookInfo(BookInfo* info,FILE* inptr);
Node* CreateNew(BookInfo data);
int InsertNewInOrder(Node** list, BookInfo data);
int DeleteLess50Pages(Node** list);
int CountNodes(const Node* list);
BookInfo* FindTop5Latest(const Node* list);
void DeleteList(Node** list);

#endif
