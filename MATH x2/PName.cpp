#define _CRT_SECURE_NO_WARNINGS

#include "PName.h"

PName* PName::ptr = NULL;
TCHAR PName::p_name[50];
Question dlgg;


PName::PName(void)
{
	ptr = this;
}

void PName::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL PName::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hGo = GetDlgItem(hwnd, IDC_GO);
	hName = GetDlgItem(hwnd, IDC_PNAME);

	


	return TRUE;
}

void PName::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_GO)
	{
		if (SendMessage(hName, EM_LINELENGTH, 0, 0) == 0)
			MessageBox(hwnd, TEXT("Enter the name"), TEXT("Error"), MB_ICONWARNING);
		else if (SendMessage(hName, EM_LINELENGTH, 0, 0) > 6)
			MessageBox(hwnd, TEXT("Name is too long (have to be 6 or less)"), TEXT("Error"), MB_ICONWARNING);
		else
		{
			SendMessage(hName, WM_GETTEXT, 100, (LPARAM)p_name);
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG5), hwnd, Question::DlgProc);
			EndDialog(hwnd, 0);
		}
	}
}

BOOL CALLBACK PName::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}