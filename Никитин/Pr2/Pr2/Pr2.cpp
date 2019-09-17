// Pr2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>
#include <Windows.h>
#include <TCHAR.h>
#include <winerror.h>
using namespace std;

//TCHAR

void main()
{
	WIN32_FIND_DATA s;
	HANDLE f = FindFirstFile(_T("C:\\Users\\Toshiba\\Desktop\\Никитин\\*.*"), &s);
	TCHAR err[256];
	if (f != INVALID_HANDLE_VALUE)
	{
		do
		{
			TCHAR* cur = s.cFileName;
			while ((*cur) && (*cur != '~')) cur++;
			if (*cur == '~')
			{
				if (!DeleteFile(s.cFileName))
				{
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), err, 255, NULL);
					printf("%ls", err);
				}
			}
		} while (FindNextFile(f, &s));
		FindClose(f);
	}
	else
	{
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), err, 255, NULL);
		printf("%ls", err);
	}
}
