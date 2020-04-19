
// --------------------------------------------------------------
//
//  Thinkpad Fan Control
//
// --------------------------------------------------------------
//
// The original TPFanControl code is in public domain. See this fork for public domain code:
// https://github.com/cjbdev/TPFanControl
// All my own patches are licensed under GNU GPL v3 license. See notice below and LICENSE file for details.
//
// Copyright (c) Stanislav Vinokurov, 2020
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.// 
//
// --------------------------------------------------------------

#ifndef FANCONTROL_H
#define FANCONTROL_H

#pragma once
#include "_prec.h"
#include "winstuff.h"
#include "TaskbarTextIcon.h"



#define FANCONTROLVERSION "0.60"

#define WM__DISMISSDLG WM_USER+5
#define WM__GETDATA WM_USER+6
#define WM__NEWDATA WM_USER+7
#define WM__TASKBAR WM_USER+8

#define setzero(adr, size) memset((void*)(adr), (char)0x00, (size))
#define ARRAYMAX(tab) (sizeof(tab)/sizeof((tab)[0]))
#define NULLSTRUCT	{ 0, }

//named pipe TPFanControl01
#define g_szPipeName "\\\\.\\Pipe\\TPFanControl01"  //Name given to the pipe
#define BUFFER_SIZE 1024 //1k

class FANCONTROL 
{
	protected:
        HINSTANCE m_hinstapp;
		HWND hwndDialog;

		UINT_PTR m_titleTimer;

		int iFarbeIconB;
		int MaxTemp;
		int iMaxTemp;
		int TaskbarNew;
		int fanspeed, showfanspeed;
		int Log2File;
		int ShowTempIcon;
		HANDLE hThread;
		HANDLE hPipe;
		char Title[128];
		char Title2[128];
		char Title3[128];
		char Title4[128];

		// dialog.cpp
		ULONG DlgProc(HWND hwnd, ULONG msg, WPARAM mp1, LPARAM mp2);
		static ULONG CALLBACK BaseDlgProc(HWND hwnd, ULONG msg, WPARAM mp1, LPARAM mp2);

        //The default app-icon with changing colors
		TASKBARICON *pTaskbarIcon;
        //Digital Text icon with changing colors
        CTaskbarTextIcon **ppTbTextIcon;

		
		static int _stdcall FANCONTROL_Thread(ULONG parm) \
			{ return ((FANCONTROL *)parm)->WorkThread(); }

		int WorkThread();


		// misc.cpp
		void Trace(const char *text);
		BOOL IsMinimized(void);
		void CurrentDateTimeLocalized(char *result, size_t sizeof_result);
		void CurrentTimeLocalized(char *result, size_t sizeof_result);
		HANDLE CreateThread(int (_stdcall *fnct)(ULONG), ULONG p);

	public:
		FANCONTROL(HINSTANCE hinstapp);
		~FANCONTROL();

		int ProcessDialog();

        HWND GetDialogWnd() { return hwndDialog; }
		HANDLE GetWorkThread() { return hThread; }

        // The texticons will be shown depending on variables
        void ProcessTextIcons();
        void RemoveTextIcons(void);
};

#endif // FANCONTROL_H