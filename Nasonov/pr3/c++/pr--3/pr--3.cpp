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
			LPTSTR cur = s.cFileName;

		
				int x = _tcslen(s.cFileName);

				if (cur[x - 1] != '!') 
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
						if (!(s.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)&&!(s.dwFileAttributes & FILE_ATTRIBUTE_DEVICE)) // проверка на диреторию
						{

							DWORDLONG dwFileSize = (s.nFileSizeHigh * (MAXDWORD + 1)) + s.nFileSizeLow;



							if (dwFileSize % 2 != 0)  // если условие окес
							{

								_tcscat(cur, _T("!"));

								_tcscat(pathSecond, cur);

								if (!MoveFile(path, pathSecond))
								{
									writeError();
								}
							}
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
	rec(_T("C:\\files\\"));
}
 