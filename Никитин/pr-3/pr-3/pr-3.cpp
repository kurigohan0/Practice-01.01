#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <TCHAR.h>
#include <winerror.h>
#include <string>
using namespace std;

void writeError()
{
	LPTSTR err = NULL;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)& err, 0, NULL);
	_tprintf(_T("%s"), err);
}

void rec(LPCTSTR str)
{
	WIN32_FIND_DATA s;
	LPTSTR file = new TCHAR[_tcslen(str) + 4];
	_tcscpy(file, str);
	_tcscat(file, _T("*.*"));
	HANDLE f = FindFirstFile(file, &s);
	if (f != INVALID_HANDLE_VALUE)
	{
		do
		{
			LPTSTR buf=NULL;
			LPTSTR cur = s.cFileName;
			while ((*cur) && (*cur != '~')) cur++;
			if ((*cur == '~') && !(FILE_ATTRIBUTE_DIRECTORY & s.dwFileAttributes) && !(FILE_ATTRIBUTE_DEVICE & s.dwFileAttributes) && (s.nFileSizeLow == 0) && (s.nFileSizeHigh == 0))
			{
					buf = new TCHAR[_tcslen(str) + _tcslen(s.cFileName)+1];
					if (buf)
					{
						_tcscpy(buf, str);
						_tcscat(buf, s.cFileName);
						if (!DeleteFile(buf))
						{
							writeError();
						}
						delete[] buf;
					}
					else
					{
						_tprintf(_T("Не хватает памяти добавь"));
					}
			}
			else
				if ((s.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (0 != _tcscmp(s.cFileName, _T("."))) && (0 != _tcscmp(s.cFileName, _T(".."))))
				{
					buf = new TCHAR[_tcslen(str) + _tcslen(s.cFileName) + 2];
					if (buf)
					{
						_tcscpy(buf, str);
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
		} while (FindNextFile(f, &s));
		if (GetLastError() != ERROR_NO_MORE_FILES)
		{
			writeError();
		}
		FindClose(f);
	}
	else
	{
		writeError();
	}
}

void main()
{
	rec(_T("C:\\Users\\Spyinfo\\Desktop\\College\\test\\"));
}