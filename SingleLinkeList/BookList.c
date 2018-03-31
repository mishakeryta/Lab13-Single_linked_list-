#define _CRT_SECURE_NO_WARNINGS
#include "BookList.h"

//--------------------------------------------------------------------------------
Tnode* CreateNew(TbookInfo info) {
	Tnode* pNewNode = (Tnode*)malloc(sizeof(Tnode));
	pNewNode->m_info = info;
	pNewNode->m_pNext = NULL;
	return pNewNode;
}
//--------------------------------------------------------------------------------
int InsertToBegin(Tnode** ppList, Tnode* pNode) {
	if (!ppList || !pNode) return 0;
	pNode->m_pNext = *ppList;
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
	if (strcmp((*ppList)->m_info.m_szAuthor, pNewNode->m_info.m_szAuthor) <= 0) {
		InsertToBegin(ppList, pNewNode);
		return 1;
	}
	Tnode* pCrawlerForList = *ppList;
	while (pCrawlerForList->m_pNext &&
		strcmp(pCrawlerForList->m_pNext->m_info.m_szAuthor,
			pNewNode->m_info.m_szAuthor) >= 0) {
		pCrawlerForList = pCrawlerForList->m_pNext;
	}
	if (!pCrawlerForList->m_pNext) {
		pCrawlerForList->m_pNext = pNewNode;
	}
	else {
		InsertToBegin(&pCrawlerForList->m_pNext, pNewNode);
	}
	return 1;
}
//--------------------------------------------------------------------------------
int DeleteHead(Tnode** ppList) {
	if (!ppList || !*ppList) {
		return 0;
	}
	Tnode* pTmpForDeletingNode = *ppList;
	*ppList = (*ppList)->m_pNext;
	free(pTmpForDeletingNode);
	return 1;
}
//--------------------------------------------------------------------------------
int DeleteLess50Pages(Tnode **ppList) {
	if (!ppList || !(*ppList)) {
		return 0;
	}
	Tnode *tmp = *ppList;
	while (*ppList && (*ppList)->m_info.m_nPages <= 50) {
		DeleteHead(ppList);
	}
	if (!*ppList || !(*ppList)->m_pNext) return 1;
	Tnode* pCrawlerForList = *ppList;
	while (pCrawlerForList->m_pNext) {
		if (pCrawlerForList->m_pNext->m_info.m_nPages <= 50) {
			DeleteHead(&pCrawlerForList->m_pNext);
		}
		else {
			pCrawlerForList = pCrawlerForList->m_pNext;
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
		TbookInfo tmp = pList->m_info;
		const Tnode* pCrawlerForList = pList;
		int nNumOfNode = 0;
		int nGoingInNode = 0;
		while (pCrawlerForList) {
			if (pCrawlerForList->m_info.m_nYear >= tmp.m_nYear &&
				!pchIsInNodeWithNum[nNumOfNode]) {
				tmp = pCrawlerForList->m_info;
				nGoingInNode = nNumOfNode;
			}
			++nNumOfNode;
			pCrawlerForList = pCrawlerForList->m_pNext;
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
		*ppList = (*ppList)->m_pNext;
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
		PrintBook(pList->m_info);
		PRINT_ROW_FOR_BOOK_TABLE();
		pList = pList->m_pNext;
	} while (pList);
}
//--------------------------------------------------------------------------------
int CountNodes(const Tnode* pList) {
	int nCount = 0;
	while (pList) {
		pList = pList->m_pNext;
		++nCount;
	}
	return nCount;
}
//--------------------------------------------------------------------------------
