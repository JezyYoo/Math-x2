#define _CRT_SECURE_NO_WARNINGS

#include "Scoreboard.h"

Scoreboard* Scoreboard::ptr = NULL;
HWND Scoreboard::hScoreboard;
Menu dlg;
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
	hClear = GetDlgItem(hwnd, IDC_CLEAR);
	hScoreboard = GetDlgItem(hwnd, SCOREBOARD);
	hSimple = GetDlgItem(hwnd, IDC_SIMPLE);
	hQuestion = GetDlgItem(hwnd, IDC_QUESTION);
	hAct = GetDlgItem(hwnd, ST_ACT);
	hDif = GetDlgItem(hwnd,ST_DIF);
	hTrue = GetDlgItem(hwnd, ST_TRUE);
	hFalse = GetDlgItem(hwnd, ST_FALSE);


	SendMessage(hSimple, BM_SETCHECK, BST_CHECKED, 0);

	return TRUE;
}

void Scoreboard::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (SendMessage(hSimple, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		LoadSimple();
		SetWindowText(hAct, TEXT("Act"));
		SetWindowText(hDif, TEXT("Dificulty"));
		SetWindowText(hTrue, TEXT("True"));
		SetWindowText(hFalse, TEXT("False"));
	}
	if (SendMessage(hQuestion, BM_GETCHECK, 0, 0) == BST_CHECKED)
	{
		LoadQuestion();
		SetWindowText(hAct, TEXT("True"));
		SetWindowText(hDif, TEXT("False"));
		SetWindowText(hTrue, TEXT(""));
		SetWindowText(hFalse, TEXT(""));
	}

	if (id == IDC_CLEAR)
	{
		SendMessage(hScoreboard, LB_RESETCONTENT, 0, 0);
		if (SendMessage(hSimple, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			fstream clear_file("scoreboard.txt", ios::out);
			clear_file.close();
			dlg.score.clear();
		}
		else if (SendMessage(hQuestion, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			fstream clear_file("scoreboard2.txt", ios::out);
			clear_file.close();
			dlg.score2.clear();
		}
		
	}
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

void Scoreboard::LoadSimple()
{
	SendMessage(hScoreboard, LB_RESETCONTENT, 0, 0);
	for (size_t i = 0; i < dlg.score.size(); i++)
	{
		buff = (TCHAR*)dlg.score[i].c_str();
		SendMessage(hScoreboard, LB_ADDSTRING, 0, (LPARAM)buff);
	}
}

void Scoreboard::LoadQuestion()
{
	SendMessage(hScoreboard, LB_RESETCONTENT, 0, 0);
	for (size_t i = 0; i < dlg.score2.size(); i++)
	{
		buff = (TCHAR*)dlg.score2[i].c_str();
		SendMessage(hScoreboard, LB_ADDSTRING, 0, (LPARAM)buff);
	}
}
