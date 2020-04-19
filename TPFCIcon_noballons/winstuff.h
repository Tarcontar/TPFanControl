
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

#ifndef WINCONTROLS_H
#define WINCONTROLS_H

#pragma once

#include "_prec.h"


#ifndef NIF_STATE			// NotifyIcon V5 defines
	#define NIF_STATE       0x00000008
	#define NIF_INFO        0x00000010
	#define NIF_GUID        0x00000020

	#define NIIF_INFO       0x00000001
	#define NIIF_WARNING    0x00000002
	#define NIIF_ERROR      0x00000003
	#define NIIF_ICON_MASK  0x0000000F
	#define NIIF_NOSOUND    0x00000010
#endif


class TASKBARICON {

	private:
		BOOL UpAndRunning;

	protected: 
		HWND Owner;
		int Id, IconId;
		char Tooltip[256];
		int osVersion; //TODO: war drin?
		volatile BOOL InsideTooltipRebuild; //should be declared as volatile for concurrency reasons


	public:
		TASKBARICON(HWND hwndowner, int id, const char *tooltip);
		~TASKBARICON(void);

		BOOL Construct(void);
		void Destroy(BOOL keep= FALSE);

		BOOL RebuildIfNecessary(BOOL);

		BOOL IsUpAndRunning(void);
		int SetIcon(int iconid);
		int SetTooltip(const char *tip);
		int SetBalloon(ULONG flags, const char *title, const char *text, int timeout= 2);
}; 


class MENU {

	private:

	protected: 
		BOOL IsLoaded;
		HMENU hMenu;
		HWND hWndOwner;

	public:
		MENU(HWND hwnd);
		MENU(HMENU hm);
		MENU(int id, HINSTANCE hdll= (HINSTANCE)(ULONG)-1);
		~MENU()
			{ if (this->IsLoaded) ::DestroyMenu(this->hMenu); this->hMenu= NULL; }

		operator HMENU(void) const
				{ return (HMENU)this->hMenu; }

		int GetNumMenuItems(void);
		BOOL IsMenuItemSeparator(int pos);

		void EnableMenuItem(int id, int status= TRUE);
		void DisableMenuItem(int id);
		int DeleteMenuItem(int id, BOOL idispos= FALSE);
		BOOL InsertItem(const char *text, int id, int pos= -1);
		BOOL InsertMenuItem(const char *text, int id, int pos= -1)
				{ return this->InsertItem(text, id, pos); }
		BOOL InsertSeparator(int pos)
				{ return this->InsertItem(NULL, 0, pos); }
		void CheckMenuItem(int id, int status= TRUE);
		void UncheckMenuItem(int id);
		BOOL IsFlags(int id, int flags);
		BOOL IsMenuItemEnabled(int id);
		BOOL IsMenuItemDisabled(int id);
		BOOL IsMenuItemChecked(int id);
	
		HMENU GetSubmenuFromPos(int pos);
		int GetMenuPosFromID(int id);

		int Popup(HWND hwnd, POINT *ppoint= NULL, BOOL synchtrack= FALSE);
};

#endif // WINCONTROLS_H