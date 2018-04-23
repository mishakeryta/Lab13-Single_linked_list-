#define _CRT_SECURE_NO_WARNINGS
#include "BookList.h"

//--------------------------------------------------------------------------------
Tnode* CreateNew(TbookInfo info) {
	Tnode* pNewNode = (Tnode*)malloc(sizeof(Tnode));
	pNewNode->info = info;
	pNewNode->pNext = NULL;
	return pNewNode;
}
//--------------------------------------------------------------------------------
int InsertToBegin(Tnode** ppList, Tnode* pNode) {
	if (!ppList || !pNode) return 0;
	pNode->pNext = *ppList;
	(*ppList) = pNode;
	return 1;
}
//--------------------------------------------------------------------------------
int InsertNewInOrder(Tnode** ppList, TbookInfo info) {
	if (!ppList) return 0;
	Tnode* pNewNode = CreateNew(info);
	if (!(*ppList)) {
		*ppList = pNewNode;
		return 1;
	}
	if (strcmp((*ppList)->info.szAuthor, pNewNode->info.szAuthor) <= 0) {
		InsertToBegin(ppList, pNewNode);
		return 1;
	}
	Tnode* pCrawlerForList = *ppList;
	while (pCrawlerForList->pNext &&
		strcmp(pCrawlerForList->pNext->info.szAuthor,
			pNewNode->info.szAuthor) >= 0) {
		pCrawlerForList = pCrawlerForList->pNext;
	}
	if (!pCrawlerForList->pNext) {
		pCrawlerForList->pNext = pNewNode;
	}
	else {
		InsertToBegin(&pCrawlerForList->pNext, pNewNode);
	}
	return 1;
}
//--------------------------------------------------------------------------------
int DeleteHead(Tnode** ppList) {
	if (!ppList || !*ppList) {
		return 0;
	}
	Tnode* pTmpForDeletingNode = *ppList;
	*ppList = (*ppList)->pNext;
	free(pTmpForDeletingNode);
	return 1;
}
//--------------------------------------------------------------------------------
int DeleteLessThen50Pages(Tnode **ppList) {
	if (!ppList || !(*ppList)) {
		return 0;
	}
	Tnode *tmp = *ppList;
	while (*ppList && (*ppList)->info.nPages <= 50) {
		DeleteHead(ppList);
	}
	if (!*ppList || !(*ppList)->pNext) return 1;
	Tnode* pCrawlerForList = *ppList;
	while (pCrawlerForList->pNext) {
		if (pCrawlerForList->pNext->info.nPages <= 50) {
			DeleteHead(&pCrawlerForList->pNext);
		}
		else {
			pCrawlerForList = pCrawlerForList->pNext;
		}
	}
	return 1;
}
//--------------------------------------------------------------------------------
TbookInfo* FindTop5Latest(const Tnode* pList) {
	if (!pList) return NULL;
	int nCountOfElements = CountNodes(pList);
	if (nCountOfElements < 5)return NULL;
	char* pchIsInNodeWithNum = (char*)calloc(nCountOfElements, sizeof(char));
	TbookInfo* pTop5LatestInfo = (TbookInfo*)calloc(5, sizeof(TbookInfo));
	for (int i = 0; i < 5; ++i) {
		TbookInfo tmp = pList->info;
		const Tnode* pCrawlerForList = pList;
		int nNumOfNode = 0;
		int nGoingInNode = 0;
		while (pCrawlerForList) {
			if(pchIsInNodeWithNum[nGoingInNode]){
				tmp = pCrawlerForList->info;
				nGoingInNode = nNumOfNode;
			} else if (pCrawlerForList->info.nYear >= tmp.nYear &&
				!pchIsInNodeWithNum[nNumOfNode]) {
				tmp = pCrawlerForList->info;
				nGoingInNode = nNumOfNode;
			}
			++nNumOfNode;
			pCrawlerForList = pCrawlerForList->pNext;
		}
		pTop5LatestInfo[i] = tmp;
		pchIsInNodeWithNum[nGoingInNode] = 1;
	}
	return pTop5LatestInfo;
}
//--------------------------------------------------------------------------------
int DeleteList(Tnode **ppList) {
	if (!ppList) return 0;
	Tnode* pTmpForDeletingNode = NULL;
	while (*ppList) {
		pTmpForDeletingNode = *ppList;
		*ppList = (*ppList)->pNext;
		free(pTmpForDeletingNode);
	}
	return 1;
}
//--------------------------------------------------------------------------------
void PrintListBooks(const Tnode* pList) {
	if (!pList) {
		return;
	}
	PRINT_ROW_FOR_BOOK_TABLE();
	PrintTemplate();
	PRINT_ROW_FOR_BOOK_TABLE();
	do {
		PrintBook(pList->info);
		PRINT_ROW_FOR_BOOK_TABLE();
		pList = pList->pNext;
	} while (pList);
}
//--------------------------------------------------------------------------------
int CountNodes(const Tnode* pList) {
	int nCount = 0;
	while (pList) {
		pList = pList->pNext;
		++nCount;
	}
	return nCount;
}
//--------------------------------------------------------------------------------
