#include "BookInfo.h"

//провіряє чи символ може міститися у імені автора
int IsAuthorChar(int chr) {
	return isalpha(chr) || isblank(chr) || chr == '-';
}
//провіряє чи символ може міститися у назві книги
int IsNameBookChar(int chr) {
	return  IsAuthorChar(chr) || isdigit(chr);
}
//провіряє чи символ може міститися у цифрі з плавючою комою
int IsFloatDiginChar(int chr) {
	return isdigit(chr) || chr == '.';
}

//видаляє всі символи сhr , що входять у стрічку
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

