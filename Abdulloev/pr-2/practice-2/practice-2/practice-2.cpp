#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <TCHAR.h>
#include <winerror.h>
#include <clocale>
using namespace std;


/// Вывод ошибки
void writeError() {
	LPTSTR err = NULL;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)& err, 0, NULL);
	cout << err << GetLastError() << '\n';
	_tprintf(_T("%s"), err);
}



int main()
{
	setlocale(LC_ALL, "Russian");
	WIN32_FIND_DATA s;
	HANDLE f = FindFirstFile(_T("C:\\Users\\Spyinfo\\Desktop\\College\\test\\*.*"), &s);
	if (f != INVALID_HANDLE_VALUE)
	{
		int x = 0;
		do
		{
			LPCTSTR cur = s.cFileName;
			
			int countOfVowels = 0; // кол-во гласных в имени файла

			while ((*cur) && (countOfVowels < 3)) {

				switch (*(cur++)) {
					case 'a':
					case 'o':
					case 'i':
					case 'e':
					case 'u':
					case 'y':
					case 'A':
					case 'O':
					case 'I':
					case 'E':
					case 'U':
					case 'Y':
						++countOfVowels;
						break;
				}
			}

			if (countOfVowels == 2) { // Если имя файла содержит 2 гласные буквы
				TCHAR path[256] = _T("C:\\Users\\Spyinfo\\Desktop\\College\\test\\");
				TCHAR pathSecond[256] = _T("C:\\Users\\Spyinfo\\Desktop\\College\\test\\");

				 
				LPTSTR old = s.cFileName;
				old++;
				
				_tcscat(pathSecond, old);
				_tcscat(path, s.cFileName);

				if (MoveFile(path, pathSecond)) 
				{
					printf("Успешно %ls\n", old);
				}
			
				else // если не получилось переименовать
				{
					writeError();
				}
			}

		} while (x = FindNextFile(f, &s));

		if ((GetLastError() != ERROR_NO_MORE_FILES))
		{
			writeError();
		}
		FindClose(f);
	}
	else // если не получилось прочитать 1-й файл в директории
	{
		writeError();
	}
}
