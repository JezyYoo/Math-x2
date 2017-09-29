#define _CRT_SECURE_NO_WARNINGS

#include "Scoreboard.h"

Scoreboard* Scoreboard::ptr = NULL;
HWND Scoreboard::hScoreboard;
Math dlg;
TCHAR *buff;

Scoreboard::Scoreboard(void)
{
	ptr = this;
}

void Scoreboard::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Scoreboard::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hScoreboard = GetDlgItem(hwnd, SCOREBOARD);

	SendMessage(hScoreboard, LB_RESETCONTENT, 0, 0);
	for (size_t i = 0; i < dlg.score.size(); i++)
	{
		buff = (TCHAR*)dlg.score[i].c_str();
		SendMessage(hScoreboard, LB_ADDSTRING, 0, (LPARAM)buff);
	}
	
	return TRUE;
}

void Scoreboard::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
}

BOOL CALLBACK Scoreboard::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}