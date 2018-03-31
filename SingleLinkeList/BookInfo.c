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
//провіряє ,чи символ може міститися у імені автора,
//повертає не  нуль, якщо так, інакше нуль.
int IsAuthorChar(int ch) {
	return isalpha(ch) || isblank(ch) || ch == '-';
}
//--------------------------------------------------------------------------------
//провіряє ,чи символ може міститися у назві книги,
//повертає не  нуль, якщо так, інакше нуль.
int IsNameBookChar(int ch) {
	return  IsAuthorChar(ch) || isdigit(ch);
}
//--------------------------------------------------------------------------------
//провіряє чи символ може міститися у цифрі з плавючою комою
//повертає не  нуль, якщо так, інакше нуль.
int IsFloatDiginChar(int ch) {
	return isdigit(ch) || ch == '.';
}
//--------------------------------------------------------------------------------
//видаляє всі символи сh , що входять у стрічку,
//доступна лише в межах цбого файлу,
//повертає 1 , якщо все пройшдо без помилок добре інакше 0
//Приклад:
//char str[] = "111112";
//DeleteAll('1',str);
//В результаті str буде дорівнювати "2";
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
//Функція яка забирає лишні пробіли,та провіряє наявність тире підряд,
//або  пред іменем.Повертає 0 якщо формат імені не відповідпє нормам,інаше 1.
int FormatAuthor(char* szName) {
	int nWasAlpha = 0;
	if (!szName) return 0;
	int nBlankZoneHaveDash = 0;
	if (isalpha(szName[0])) nWasAlpha = 1;
	if (szName[0] == '-') return 0;
	//+ це символ , що буде видалений зі стрічки
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
//Копіює всі символи, доки не знайде символ chEndOfSource.
//check вказівник на функцію.Провіряє символи, чи входять вони у відповідні межі.
//Яущо символ не підходить під умову сheck, вся функція повертає 0
//Якщо розмір рядка призначення менший з кількість символів, що доступно,
//функція поверне 0.
//Якщо функція не знайшла endOfSource повертає 0.
// В усіх інших випадках повертає 1;
//Приклад:
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
//Провіряє ,чи відподає szPrice фомату ціни.
//Повертає 1 якщо так, 0 якщо ні.
int CheckPriceFormatIsTrue(char* szPrice) {
	if (!szPrice) return 0;
	//кількість крапок , кількість цифр після крапки
	int nNumDot = 0, nNumDigitsAfterDot = 0;
	//цикл, який  проходтиться по рядку
	for (int i = 0, nLength = strlen(szPrice); i < nLength; ++i) {
		//якщо була крапка збільшити кількість цифр після неї
		if (nNumDot) ++nNumDigitsAfterDot;
		//якщо крапка, збільшити кількість крапок
		if (szPrice[i] == '.') ++nNumDot;
		//якщо це не число і не крапка або цількість крапок білше за одну  або кільк. циф після крап. білше за 2
		if (!(isdigit(szPrice[i]) || szPrice[i] == '.') || nNumDot >= 2 || nNumDigitsAfterDot > 2) return 0;
	}
	return 1;
}
//--------------------------------------------------------------------------------
int ReadBookInfoFromFile(TbookInfo* info, FILE* pfInput) {
	//перевірка, чи було предано NULL вказівник 
	if (!info || !pfInput) return 0;
	//буфер для збергання рядку з даними
	char szBuffer[BUFFER_SIZE] = { 0 };
	//зчитування з потоку даних
	if (!fgets(szBuffer, BUFFER_SIZE - 1, pfInput)) return 0;
	//змінна, яка зберігає позицію в буфері
	int nIndexOfBuffer = 0;
	//копіювання з буферу імені автора, якщо щось пішло не так, повернути -1, що означає помилку форматування
	if (!(nIndexOfBuffer = GetStrTo(info->m_szAuthor, SIZE_NAMES, '|', IsAuthorChar, szBuffer))) return -1;
	//перевірка формату імені, видалення лишніх пробілів, якщо формат не правильний, якщо щось пішло не так ...
	if (!FormatAuthor(info->m_szAuthor)) return -1;
	//пропуск риски в буфері
	++nIndexOfBuffer;

	//добавлення  з мінної яка зберігає зміщення позиції буферу в функції
	int nIndexLocalBuffer = 0;
	//зчитування імені книги з буферу(теперішньої позиції),зберігання зміщення 
	if (!(nIndexLocalBuffer = GetStrTo(info->m_szName, SIZE_NAMES, '|', IsNameBookChar, szBuffer + nIndexOfBuffer))) return -1;
	//прехід на настувну позицію
	nIndexOfBuffer += nIndexLocalBuffer + 1;

	//стрічка(масив сисволив) ,яка зберігає стрічкове представлення року,кількості сторінок,ціни
	char szTmpForDigits[MAX_LENGHT_OF_NUMBER] = { 0 };
	//видалення всіх пробілів ,які йдуть після нашої позиції в буфері
	DeleteAll(' ', szBuffer + nIndexOfBuffer);
	//зчитування стрічкового представлення року видвння книги з буферу(теперішньої позиції),зберігання зміщення 
	if (!(nIndexLocalBuffer = GetStrTo(
		szTmpForDigits,
		MAX_LENGHT_OF_NUMBER,
		'|',
		isdigit,
		szBuffer + nIndexOfBuffer))) return -1;

	//перехід на нову позію 
	nIndexOfBuffer += nIndexLocalBuffer + 1;
	//конвертування та збереження року
	info->m_nYear = atoi(szTmpForDigits);

	//те саме  зі сторінками
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

	// превірка формату ціни
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
