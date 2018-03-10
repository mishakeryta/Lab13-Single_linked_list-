#include "BookInfo.h"

//������� �� ������ ���� �������� � ���� ������
int IsAuthorChar(int chr) {
	return isalpha(chr) || isblank(chr) || chr == '-';
}
//������� �� ������ ���� �������� � ���� �����
int IsNameBookChar(int chr) {
	return  IsAuthorChar(chr) || isdigit(chr);
}
//������� �� ������ ���� �������� � ���� � �������� �����
int IsFloatDiginChar(int chr) {
	return isdigit(chr) || chr == '.';
}

//������� �� ������� �hr , �� ������� � ������
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
//������� ��� ������ ���� ������,�� ������� �������� ���� �����, ���  ���� ������
int FormatAuthor(char* name) {
	int wasAlpha = 0;
	int blankZoneHaveDash = 0;
	if (isalpha(name[0])) wasAlpha = 1;
	if (name[0] == '-') return 0;
	//+ �� ������ , �� ���� ��������� �� ������
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

/*������� ��� ����� �� �������, ���� �� ������ ������ endOfSource
*������� 1 ���� ���� ������� ������, � � str ��������� ������
*check ������� ,��� � ������ ������� �������*/
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

//������� ��� ������� ����� �� �������� ���� ���, ��� ����� 2 ����� ���� ����
int CheckPriceFormatIsTrue(char* price) {
	if (!price) return 0;
	//������� ������ , ������� ���� ���� ������
	int numDot = 0, numDigitsAfterDot = 0;
	//����, ����  ������������ �� �����
	for (int i = 0, length = strlen(price); i < length; ++i) {
		//���� ���� ������ �������� ������� ���� ���� ��
		if (numDot) ++numDigitsAfterDot;
		//���� ������, �������� ������� ������
		if (price[i] == '.') ++numDot;
		//���� �� �� ����� � �� ������ ��� �������� ������ ���� �� ����  ��� ����. ��� ���� ����. ���� �� 2
		if (!(isdigit(price[i]) || price[i] == '.') || numDot >= 2 || numDigitsAfterDot > 2) return 0;
	}
	return 1;
}
//�������,��� ����� ��� � ������(���������, ����� ������������) 
int FReadBookInfo(BookInfo* info, FILE* inptr) {
	//��������, �� ���� ������� NULL �������� 
	if (!info || !inptr) return 0;
	//����� ��� ��������� ����� � ������
	char buffer[BUFFER_SIZE] = { 0 };
	//���������� � ������ �����
	if (!fgets(buffer, BUFFER_SIZE - 1, inptr)) return 0;
	//�����, ��� ������ ������� � �����
	int indexOfBuffer = 0;
	//��������� � ������ ���� ������, ���� ���� ���� �� ���, ��������� -1, �� ������ ������� ������������
	if (!(indexOfBuffer = GetStrTo(info->author, SIZE_NAMES, '|', IsAuthorChar, buffer))) return -1;
	//�������� ������� ����, ��������� ����� ������, ���� ������ �� ����������, ���� ���� ���� �� ��� ...
	if (!FormatAuthor(info->author)) return -1;
	//������� ����� � �����
	++indexOfBuffer;

	//����������  � ���� ��� ������ ������� ������� ������ � �������
	int indexLocalBuffer = 0;
	//���������� ���� ����� � ������(��������� �������),��������� ������� 
	if (!(indexLocalBuffer = GetStrTo(info->name, SIZE_NAMES, '|', IsNameBookChar, buffer + indexOfBuffer))) return -1;
	//������ �� �������� �������
	indexOfBuffer += indexLocalBuffer + 1;

	//������(����� ��������) ,��� ������ �������� ������������� ����,������� �������,����
	char tmpForDigits[12] = { 0 };
	//��������� ��� ������ �� ����� ���� ���� ������� � �����
	DeleteAll(' ', buffer + indexOfBuffer);
	//���������� ���������� ������������� ���� ������� ����� � ������(��������� �������),��������� ������� 
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	//������� �� ���� ���� 
	indexOfBuffer += indexLocalBuffer + 1;
	//������������� �� ���������� ����
	info->year = atoi(tmpForDigits);

	//�� ����  � ���������
	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '|', isdigit, buffer + indexOfBuffer))) return -1;
	indexOfBuffer += indexLocalBuffer + 1;
	info->pages = atoi(tmpForDigits);
	if (info->pages <= 0) return -1;

	if (!(indexLocalBuffer = GetStrTo(tmpForDigits, 12, '\n', IsFloatDiginChar, buffer + indexOfBuffer))) return -1;
	// ������� ������� ����
	if (!CheckPriceFormatIsTrue(tmpForDigits)) return -1;
	info->price = atof(tmpForDigits);

	return 1;
}

