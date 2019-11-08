/******************************************************************
*   21 days: a game for programmers
*   Copyright (C) 2014 Maxim Grishin
*
*   This program is free software; you can redistribute it and/or
*   modify it under the terms of the GNU General Public License
*   as published by the Free Software Foundation; either version 2
*   of the License, or (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*   MA  02110-1301, USA.
*******************************************************************/

#ifndef H_INTERFACE
#define H_INTERFACE
#include <string>

wchar_t getAnswer(char a1, char a2);
wchar_t getAnswer(char a1, char a2, char a3);
wchar_t getAnswer(char a1, char a2, char a3, char a4);
wchar_t getKey();
void clearBuffer();

#ifdef _KOS32
using std::wstring;
wstring itos(int n);
wstring txt(string s, int d);
wstring txt(string s, string s2);
wstring txt(string s, string s2, string s3);

wstring txt(string s, wchar_t c);
wstring txt(string s, wchar_t ch, string s2);
wstring txt(string s, wchar_t ch, string s2, char ch2);

wstring txt(string s, int d1, int d2);
wstring txt(string s, int d1, int d2, int d3);
wstring txt(string s, int d1, int d2, int d3, int d4);

#else
std::wstring txt(const wchar_t* s, ...);
#endif

void wait(wchar_t a = ENTER_KEY, char b = ENTER_KEY);
void drawWindow(std::wstring content, const wchar_t* title = 0, std::wstring topline = L"", std::wstring bottomline = L"", bool usePagesForLongText = false);
void drawModalWindow(const wchar_t* content , const wchar_t* title = 0, const wchar_t* buttons = 0);
#endif
