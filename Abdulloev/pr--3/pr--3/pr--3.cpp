#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <TCHAR.h>
#include <winerror.h>
#include <clocale>
#include <string>
using namespace std;


/// Вывод ошибки
void writeError() {
	LPTSTR err = NULL;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)& err, 0, NULL);
	cout << err << GetLastError() << '\n';
	_tprintf(_T("%s"), err);
}

void rec(LPCTSTR name)
{
	WIN32_FIND_DATA s;
	LPTSTR n = new TCHAR[_tcslen(name) + 4];
	_tcscpy(n, name);
	_tcscat(n, _T("*"));
	HANDLE f = FindFirstFile(n, &s);
	if (f != INVALID_HANDLE_VALUE)
	{
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

			if (countOfVowels == 2)  // если имя файла содержит 2 гласные буквы
			{ 
				LPTSTR path = new TCHAR[_tcslen(name) + _tcslen(s.cFileName) + 1];
				if (path) // выделена ли память
				{
					_tcscpy(path, name);
					_tcscat(path, s.cFileName);
				}
				else // нехватка памяти
				{

					_tprintf(_T("Не хватает памяти!"));
				}
				
				LPTSTR pathSecond = new TCHAR[_tcslen(name) + _tcslen(s.cFileName) + 1];
				if (pathSecond) // 
				{
					_tcscpy(pathSecond, name);
					if (!(s.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // проверка на диреторию
					{
						LPTSTR old = new TCHAR[_tcslen(s.cFileName)+1];
						_tcscpy(old, s.cFileName);
						old++;

						_tcscat(pathSecond, old);

						if (!MoveFile(path, pathSecond))
						{
							writeError();
						}
						delete[] pathSecond;
						delete[] path;
					}
					else
					{
						if ((s.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (0 != _tcscmp(s.cFileName, _T("."))) && (0 != _tcscmp(s.cFileName, _T("..")))) // пропускеаем . и ..
						{
							LPTSTR buf = new TCHAR[_tcslen(name) + _tcslen(s.cFileName) + 3];
							if (buf)
							{
								_tcscpy(buf, name);
								_tcscat(buf, s.cFileName);
								_tcscat(buf, _T("\\"));
								rec(buf);
								delete[] buf;
							}
							else
							{
								_tprintf(_T("Не хватает памяти добавь"));
							}
						}
					}
				}
				else
				{
					_tprintf(_T("Не хватает памяти добавь"));
				}
			}

		} while (FindNextFile(f, &s));

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

int main()
{
	rec(_T("C:\\Users\\Spyinfo\\Desktop\\College\\test\\"));
}
 