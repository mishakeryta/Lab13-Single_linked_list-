#define _CRT_SECURE_NO_WARNINGS
#include "BookInfo.h"
#define PRINT_ROW_FOR_BOOK_TABLE() PrintRows(NUM_OF_COLS\
,SIZE_OF_COL_WITH_NAMES\
,SIZE_OF_COL_WITH_NAMES\
,SIZE_OF_COL_WITH_NUMBERS\
,SIZE_OF_COL_WITH_NUMBERS\
,SIZE_OF_COL_WITH_NUMBERS)
//--------------------------------------------------------------------------------
void PrintRows(int nNum, ...) {
	putchar('+');
	va_list listOfParams;
	va_start(listOfParams, nNum);
	int nNumRow = 0;
	for (int i = 0; i < nNum; i++) {
		nNumRow = va_arg(listOfParams, int);
		for (int j = 0; j < nNumRow; ++j) {
			putchar('-');
		}
		putchar('+');
	}
	va_end(listOfParams);
	putchar('\n');
}
//--------------------------------------------------------------------------------
//������� ,�� ������ ���� �������� � ���� ������,
//������� ��  ����, ���� ���, ������ ����.
int IsAuthorChar(int ch) {
	return isalpha(ch) || isblank(ch) || ch == '-';
}
//--------------------------------------------------------------------------------
//������� ,�� ������ ���� �������� � ���� �����,
//������� ��  ����, ���� ���, ������ ����.
int IsNameBookChar(int ch) {
	return  IsAuthorChar(ch) || isdigit(ch);
}
//--------------------------------------------------------------------------------
//������� �� ������ ���� �������� � ���� � �������� �����
//������� ��  ����, ���� ���, ������ ����.
int IsFloatDiginChar(int ch) {
	return isdigit(ch) || ch == '.';
}
//--------------------------------------------------------------------------------
//������� �� ������� �h , �� ������� � ������,
//�������� ���� � ����� ����� �����,
//������� 1 , ���� ��� ������� ��� ������� ����� ������ 0
//�������:
//char str[] = "111112";
//DeleteAll('1',str);
//� ��������� str ���� ���������� "2";
static int DeleteAll(char ch, char*szDestination) {
	if (!szDestination) return 0;
	for (int i = 0, nLength = strlen(szDestination); i < nLength; ++i) {
		if (szDestination[i] == ch) {
			int nStartOfDelete = i;
			do {
				++i;
			} while (szDestination[i] == ch);
			strcpy(szDestination + nStartOfDelete, szDestination + i);
			i = nStartOfDelete;
		}
	}
	return 1;
}
//--------------------------------------------------------------------------------
//������� ��� ������ ���� ������,�� ������� �������� ���� �����,
//���  ���� ������.������� 0 ���� ������ ���� �� ������� ������,����� 1.
int FormatAuthor(char* szName) {
	int nWasAlpha = 0;
	if (!szName) return 0;
	int nBlankZoneHaveDash = 0;
	if (isalpha(szName[0])) nWasAlpha = 1;
	if (szName[0] == '-') return 0;
	//+ �� ������ , �� ���� ��������� � ������
	if (szName[0] == ' ') szName[0] = '+';
	for (int i = 1, length = strlen(szName); i < length; ++i) {
		if (szName[i] == '-') {
			if (!nWasAlpha || nBlankZoneHaveDash) { return 0; 
			}else {
				nBlankZoneHaveDash = 1;
			}
			if (szName[i - 1] == ' ') {
				szName[i - 1] = '+';
			}
		}
		if (isblank(szName[i])) {
			if (szName[i - 1] == ' ' || szName[i - 1] == '+') {
				szName[i] = '+';
			}
		}
		if (isalpha(szName[i])) {
			nWasAlpha = 1;
			nBlankZoneHaveDash = 0;
		}
	}
	if (!DeleteAll('+', szName)) return 0;
	return 1;
}
//--------------------------------------------------------------------------------
//����� �� �������, ���� �� ������ ������ chEndOfSource.
//check �������� �� �������.������� �������, �� ������� ���� � ������� ���.
//���� ������ �� �������� �� ����� �heck, ��� ������� ������� 0
//���� ����� ����� ����������� ������ � ������� �������, �� ��������,
//������� ������� 0.
//���� ������� �� ������� endOfSource ������� 0.
// � ��� ����� �������� ������� 1;
//�������:
//GetStrTo(szDestination, nSizeOfDestination, chLimit, isdigit,szSource);
int GetStrTo(char* szDestination,
	int nSizeOfDestination,
	char chEndOfSource,
	int(*pfuncCheck)(int),
	char* szSource) {
	if (!szDestination || !szSource || !pfuncCheck) return 0;
	for (int i = 0; i < nSizeOfDestination; ++i) {
		if (szSource[i] == chEndOfSource) {
			szDestination[i] = 0;
			return i;
		}
		if (!pfuncCheck(szSource[i])) return 0;
		szDestination[i] = szSource[i];
	}
	return 0;
}
//--------------------------------------------------------------------------------
//������� ,�� ������ szPrice ������ ����.
//������� 1 ���� ���, 0 ���� �.
int CheckPriceFormatIsTrue(char* szPrice) {
	if (!szPrice) return 0;
	//������� ������ , ������� ���� ���� ������
	int nNumDot = 0, nNumDigitsAfterDot = 0;
	//����, ����  ������������ �� �����
	for (int i = 0, nLength = strlen(szPrice); i < nLength; ++i) {
		//���� ���� ������ �������� ������� ���� ���� ��
		if (nNumDot) ++nNumDigitsAfterDot;
		//���� ������, �������� ������� ������
		if (szPrice[i] == '.') ++nNumDot;
		//���� �� �� ����� � �� ������ ��� �������� ������ ���� �� ����  ��� ����. ��� ���� ����. ���� �� 2
		if (!(isdigit(szPrice[i]) || szPrice[i] == '.') || nNumDot >= 2 || nNumDigitsAfterDot > 2) return 0;
	}
	return 1;
}
//--------------------------------------------------------------------------------
int ReadBookInfoFromFile(TbookInfo* info, FILE* pfInput) {
	//��������, �� ���� ������� NULL �������� 
	if (!info || !pfInput) return 0;
	//����� ��� ��������� ����� � ������
	char szBuffer[BUFFER_SIZE] = { 0 };
	//���������� � ������ �����
	if (!fgets(szBuffer, BUFFER_SIZE - 1, pfInput)) return 0;
	//�����, ��� ������ ������� � �����
	int nIndexOfBuffer = 0;
	//��������� � ������ ���� ������, ���� ���� ���� �� ���, ��������� -1, �� ������ ������� ������������
	if (!(nIndexOfBuffer = GetStrTo(info->m_szAuthor, SIZE_NAMES, '|', IsAuthorChar, szBuffer))) return -1;
	//�������� ������� ����, ��������� ����� ������, ���� ������ �� ����������, ���� ���� ���� �� ��� ...
	if (!FormatAuthor(info->m_szAuthor)) return -1;
	//������� ����� � �����
	++nIndexOfBuffer;

	//����������  � ���� ��� ������ ������� ������� ������ � �������
	int nIndexLocalBuffer = 0;
	//���������� ���� ����� � ������(��������� �������),��������� ������� 
	if (!(nIndexLocalBuffer = GetStrTo(info->m_szName, SIZE_NAMES, '|', IsNameBookChar, szBuffer + nIndexOfBuffer))) return -1;
	//������ �� �������� �������
	nIndexOfBuffer += nIndexLocalBuffer + 1;

	//������(����� ��������) ,��� ������ �������� ������������� ����,������� �������,����
	char szTmpForDigits[MAX_LENGHT_OF_NUMBER] = { 0 };
	//��������� ��� ������ ,�� ����� ���� ���� ������� � �����
	DeleteAll(' ', szBuffer + nIndexOfBuffer);
	//���������� ���������� ������������� ���� ������� ����� � ������(��������� �������),��������� ������� 
	if (!(nIndexLocalBuffer = GetStrTo(
		szTmpForDigits,
		MAX_LENGHT_OF_NUMBER,
		'|',
		isdigit,
		szBuffer + nIndexOfBuffer))) return -1;

	//������� �� ���� ���� 
	nIndexOfBuffer += nIndexLocalBuffer + 1;
	//������������� �� ���������� ����
	info->m_nYear = atoi(szTmpForDigits);

	//�� ����  � ���������
	if (!(nIndexLocalBuffer = GetStrTo(
		szTmpForDigits,
		MAX_LENGHT_OF_NUMBER,
		'|',
		isdigit,
		szBuffer + nIndexOfBuffer))) return -1;

	nIndexOfBuffer += nIndexLocalBuffer + 1;
	info->m_nPages = atoi(szTmpForDigits);
	if (info->m_nPages <= 0) return -1;

	if (!(nIndexLocalBuffer = GetStrTo(
		szTmpForDigits,
		MAX_LENGHT_OF_NUMBER,
		'\n',
		IsFloatDiginChar,
		szBuffer + nIndexOfBuffer))) return -1;

	// ������� ������� ����
	if (!CheckPriceFormatIsTrue(szTmpForDigits)) return -1;
	info->m_dPrice = atof(szTmpForDigits);
	return 1;
}
//--------------------------------------------------------------------------------
int PrintBookToFile(TbookInfo info, FILE* pfOutput) {
	if (!pfOutput) return 0;
	fprintf(pfOutput,
		"%s|%s|%i|%i|%lf\n",
		info.m_szAuthor,
		info.m_szName,
		info.m_nYear,
		info.m_nPages,
		info.m_dPrice);
	return 1;
}
//--------------------------------------------------------------------------------
int IsBooksEqual(TbookInfo info1, TbookInfo info2)
{
	if (strcmp(info1.m_szAuthor, info2.m_szAuthor)
		|| strcmp(info1.m_szName, info2.m_szName)
		|| info1.m_nYear != info2.m_nYear
		|| info1.m_nPages != info2.m_nPages
		|| info1.m_dPrice != info2.m_dPrice) return 0;
	return 1;
}

//--------------------------------------------------------------------------------
void PrintArrayBooks(const TbookInfo* pInfo, int nNum) {
	if (!pInfo) {
		return;
	}
	PRINT_ROW_FOR_BOOK_TABLE();
	PrintTemplate();
	PRINT_ROW_FOR_BOOK_TABLE();
	for (int i = 0; i < nNum; ++i) {
		PrintBook(pInfo[i]);
		PRINT_ROW_FOR_BOOK_TABLE();

	}
}
//--------------------------------------------------------------------------------
void PrintTemplate(void) {
	printf("|%-*s|", SIZE_OF_COL_WITH_NAMES, "Author");
	printf("%-*s|", SIZE_OF_COL_WITH_NAMES, "Name");
	printf("%*s|", SIZE_OF_COL_WITH_NUMBERS, "Year");
	printf("%*s|", SIZE_OF_COL_WITH_NUMBERS, "Pages");
	printf("%*s|\n", SIZE_OF_COL_WITH_NUMBERS, "Price");
}
//--------------------------------------------------------------------------------
void PrintBook(TbookInfo info) {
	printf("|%-*s|", SIZE_OF_COL_WITH_NAMES, info.m_szAuthor);
	printf("%-*s|", SIZE_OF_COL_WITH_NAMES, info.m_szName);
	printf("%*i|", SIZE_OF_COL_WITH_NUMBERS, info.m_nYear);
	printf("%*i|", SIZE_OF_COL_WITH_NUMBERS, info.m_nPages);
	printf("%*.2lf|\n", SIZE_OF_COL_WITH_NUMBERS, info.m_dPrice);
}
//--------------------------------------------------------------------------------
