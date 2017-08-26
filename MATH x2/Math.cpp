
#include "Math.h"

Math* Math::ptr = NULL;

Math::Math(void)
{
	ptr = this;
}

void Math::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Math::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hEasy = GetDlgItem(hwnd, IDC_RADIO1);
	hMid = GetDlgItem(hwnd, IDC_RADIO2);
	hHard = GetDlgItem(hwnd, IDC_RADIO3);
	hAct = GetDlgItem(hwnd, ACT);
	EnableWindow(hMid, FALSE);
	EnableWindow(hHard, FALSE);

	SendMessage(hAct, CB_ADDSTRING, 0, (LPARAM)TEXT("Plus"));
	SendMessage(hAct, CB_ADDSTRING, 0, (LPARAM)TEXT("Minus"));
	SendMessage(hAct, CB_ADDSTRING, 0, (LPARAM)TEXT("Multiply"));
	SendMessage(hAct, CB_ADDSTRING, 0, (LPARAM)TEXT("Divide"));

	SendMessage(hAct, CB_SETCURSEL, 0, 0);
	SendMessage(hEasy, BM_SETCHECK, TRUE, 0);
	return TRUE;
}
Game dlg;
void Math::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case START:
		Game dlg;
		dlg.act = SendMessage(hAct, CB_GETCURSEL, 0, 0);
		if (dlg.act == -1)
		{
			break;
		}
		else
			INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Game::DlgProc);
		break;
	}
}

BOOL CALLBACK Math::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}