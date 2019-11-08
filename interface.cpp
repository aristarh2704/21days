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

#include "sys.h"

#ifndef _KOS32
#include <stdio.h> // wprintf()
#include <stdarg.h>
#define wprintf2 wprintf
#endif

#include <string> // strlen
//#include <wstring>
using std::wstring;

wchar_t getAnswer(char a1, char a2) {
    while(1) {
	if (kbhit()) {
	    wchar_t ch = getch();
	    #ifdef _KOS32
	    if (ch == 0)
	      ch = getch();
	    #endif
            if (ch == a1 || ch == a2)
                return ch;
            }
	}
    }

wchar_t getAnswer(char a1, char a2, char a3) {
    while(1) {
        if (kbhit()) {
            wchar_t ch = getch();
	    #ifdef _KOS32
	    if (ch == 0)
	      ch = getch();
	    #endif
            if (ch == a1 || ch == a2 || ch == a3)
                return ch;
            }
	}
    }

wchar_t getAnswer(char a1, char a2, char a3, char a4) {
    while(1) {
        if (kbhit()) {
            wchar_t ch = getch();
	    #ifdef _KOS32
	    if (ch == 0)
	      ch = getch();
	    #endif
            if (ch == a1 || ch == a2 || ch == a3 || ch == a4)
                return ch;
            }
	}
    }
    
void wait(wchar_t a = ENTER_KEY, char b = ENTER_KEY) {
    getAnswer(a, b);
    }
    
wchar_t getKey() {
#ifdef _KOS32
    while(1) {
    if (kbhit()) {
	wchar_t ch = getch();
	if (ch == 0)
	    ch = getch();
	return ch;
	}
    }
#else
    return getch();
#endif
    }

void blankline(int line, int width) {
    wprintf2(L"║ ");
    consoleGoto(line, width);
    wprintf2(L"║\n");
    }
    
void drawHBorder(int line, int left, int right, wchar_t l = L'╔', 
		 wchar_t c = L'═', wchar_t r = L'╗', wchar_t e = '\n') {
    consoleGoto(line, left);
    wprintf2(L"%lc", l);
    for (int i = 0; i< right - left; i++)
        wprintf2(L"%lc", c);
    consoleGoto(line, right);
    wprintf2(L"%lc%lc", r, e);
    }

void drawStringLine(int line, int left, int right, const wchar_t* str, 
		    int pos = -1, wchar_t border = L'║', bool shadow = false) {
    consoleGoto(line, left);
    if (pos == -1)
	wprintf2(L"%lc %ls", border, str);
    else {
	wprintf2(L"%lc ", border);
	consoleGoto(line, pos);
	wprintf2(L"%ls", str);
	}
    consoleGoto(line, right);
    if (shadow)
	wprintf2(L"%lc█", border);
    else
	wprintf2(L"%lc\n", border);
    }
    
void drawModalWindow(const wchar_t* content, const wchar_t* title, const wchar_t* buttons) {
    cls();  
    int winWidth, winHeight;
    getWinWH(winWidth, winHeight);
    int lines = winHeight/3;
    int msgWidth = wcslen(content)+2;

    if (msgWidth >= winWidth-4)
        msgWidth = winWidth-5;
    int msgLeft = winWidth/2 - msgWidth/2;
    int msgRight = winWidth/2 + msgWidth/2+1;
    if (msgWidth%2!=0)
        msgRight++;

    int titleWidth = 0;
    if (title != 0)
        titleWidth = wcslen(title)+2;

    drawHBorder(lines, msgLeft, msgRight,L'╒',L'═', L'╕');
    
    // title
    if (title != 0) {
        consoleGoto(lines, msgLeft+msgWidth/2-titleWidth/2);
        wprintf2(L" %ls ", title);
        }

    lines++;
    drawHBorder(lines, msgLeft, msgRight, L'│',L' ',L'│',L'█');
    lines++;
    
    //======Splitting content into pieces=========================
    int maxTextWidth = msgRight-msgLeft; // 2 borders + 2 spaces
    int start = 0;
    int len = wcslen(content);

    for (int i = 0; i < len; i++) {
        if (content[i] == '\n') {
            wstring tmp = content;
            wstring t1 = tmp.substr(start, i-start+1);
	    drawStringLine(lines, msgLeft, msgRight, t1.c_str(), -1, L'│', true);

            start = i+1;
            lines++;
            }
        else if (i - start >= maxTextWidth-3) {
            wstring tmp = content;
            wstring t1 = tmp.substr(start, i-start);
            t1+=L"\n";
	    drawStringLine(lines, msgLeft, msgRight, t1.c_str(), -1, L'│', true);
            start = i;
            lines++;
            }
        }
    if (start != len) {
        wstring tmp = content;
        wstring t1 = tmp.substr(start, len-start);
        drawStringLine(lines, msgLeft, msgRight, t1.c_str(), -1, L'│', true);
        lines++;
        }
    //===============================
    drawHBorder(lines, msgLeft, msgRight, L'│',L' ',L'│',L'█');
    lines++;

    consoleGoto(lines, msgLeft);
    wprintf2(L"│");
    if (!buttons) {
        for (int q = 0; q< msgWidth/2-4;q++)
            wprintf2(L" ");
        wprintf2(L"[Enter]");
        for (int i = 0; i< msgWidth/2-2; i++)
            wprintf2(L" ");
        }
    else {
    	int buttonsLen = wcslen(buttons);
	for (int i = 0; i < msgWidth/2-buttonsLen/2; i++)
	    wprintf2(L" ");
        wprintf2(L"%ls", buttons);
        }
    consoleGoto(lines, msgRight);
    wprintf2(L"│█");
    lines++;

    drawHBorder(lines, msgLeft, msgRight,L'└',L'─', L'┘',L'█');
    lines++;
    
    consoleGoto(lines, msgLeft+1);
    for (int i = 0; i< msgWidth+2; i++)
        wprintf2(L"▀");
    wprintf2(L" ");
    }
    
void drawWindow(wstring content, const wchar_t* title, wstring topline , wstring bottomline, bool usePagesForLongText = false) {
    cls();
    int winWidth, winHeight;
    getWinWH(winWidth, winHeight);

#if defined(_WIN32) && !defined(_KOS32)
    int deltaX = 0;
#else 
    int deltaX = 1;
#endif
    
    // Total lines
#if defined(_WIN32) && !defined(_KOS32)
    int lines = 0;
#else 
    int lines = 1;
#endif
    
    // Top
    drawHBorder(lines, deltaX, winWidth);
    lines++;

    if (topline != L"") {
	drawStringLine(lines, deltaX, winWidth, topline.c_str());
        lines++;
        }
    // Title
    if (title != 0) {
        if (topline != L"") {
            blankline(lines, winWidth);
            lines++;
        }
        drawStringLine(lines, deltaX, winWidth, title, (int)(winWidth/2.0-wcslen(title)/2.0));
        lines++;
        blankline(lines, winWidth);
        lines++;
        }

    //==========Splitting content into pieces=====================
    int maxTextWidth = winWidth-4; // 2 borders + 2 spaces
    int start = 0;
    unsigned int i = 0;
    // Let's split content into pieces if it too long or doesn't fit the screen
    while (i < content.length()) {
	if (usePagesForLongText && lines > winHeight-3) {
	  consoleGoto(lines, 0); 
	  blankline(lines, winWidth);
	  lines++;
	  drawStringLine(lines, deltaX, winWidth, L"Нажмите [Enter] для продолжения...");
	  // Bottom line
	  drawHBorder(winHeight, deltaX, winWidth,L'╚',L'═',L'╝');
	  wait();
	  // Print next page
	  cls();
	  lines = 0;
	  // Top line
	  drawHBorder(lines, deltaX, winWidth);
	  #if defined(_WIN32) && !defined(_KOS32)
	  lines = 1;
	  #else 
	  lines = 2;
	  #endif
	}
	// Use <c> tag to place text in the center
    	if (content[i] == '<') {
            // Checking for the <c> tag. <c> tag should be prepended with '\n'
            if (i+2 < content.length()) {
                if (content[i+1] == 'c' && content[i+2] == '>') {
                    // Tag found. Looking for the end of a wstring
                    int cLineEnd = content.length()-1;
                    for (unsigned int j = i; j < content.length(); j++)
                    	if (content[j] == '\n') {
                    	    cLineEnd = j;
                    	    break;
                    	    }
                    int cLineWidth = cLineEnd - i-1;
		    drawStringLine(lines, deltaX, winWidth, 
				content.substr(i+3, cLineWidth-2).c_str(), winWidth/2-cLineWidth/2);
                    i = cLineEnd+1;
                    start = i;
                    lines++;
                    continue;
                    }
                }
            }
        else if (content[i] == '\n') {
            consoleGoto(lines, 0);
            wstring t1 = content.substr(start, i-start+1);
	    drawStringLine(lines, deltaX, winWidth, t1.c_str());
            start = i+1;
            lines++;
            }
        else if ((int)i - start >= maxTextWidth-1) {
            consoleGoto(lines, 0);
            wstring t1 = content.substr(start, i-start);
            t1+=L"\n";
	    drawStringLine(lines, deltaX, winWidth, t1.c_str());
            start = i;
            lines++;
            }
          i++;
        }
    if (start <= (int)content.length()) {
        consoleGoto(lines, 0);
        wstring t1 = content.substr(start, content.length()-start);
	drawStringLine(lines, deltaX, winWidth, t1.c_str());
        lines++;
        }
    //===============================

    for (int i = lines; i< winHeight; i++) {
	blankline(lines, winWidth);
        lines++;
        }

    if (!bottomline.empty()) {
    	///Fix for long bottomline
    	if ((int)bottomline.length() >= winWidth) {
	    drawStringLine(winHeight-2, deltaX, winWidth, bottomline.substr(0, winWidth-4).c_str());
	    drawStringLine(winHeight-1, deltaX, winWidth, bottomline.substr(winWidth-4).c_str());
    	    }
    	else {
	    drawStringLine(winHeight-1, deltaX, winWidth, bottomline.c_str());
            }
        }
    // Bottom
    drawHBorder(winHeight, deltaX, winWidth,L'╚',L'═',L'╝');
    }
