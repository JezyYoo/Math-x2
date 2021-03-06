#define _CRT_SECURE_NO_WARNINGS

#include "Math.h"

Math* Math::ptr = NULL;
int Math::ls_true;
int Math::ls_false;
int Math::ls_time;
TCHAR Math::ls_mode[100];
TCHAR Math::ls_act[100];
TCHAR Math::ls_name[100];
bool Math::finished = false;

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
	hHard = GetDlgItem(hwnd, IDC_RADIO3);
	hPlus = GetDlgItem(hwnd, IDC_PLUS);
	hMinus = GetDlgItem(hwnd, IDC_MINUS);
	hDivide = GetDlgItem(hwnd, IDC_DIVIDE);
	hMulti= GetDlgItem(hwnd, IDC_MULTI);
	hLS_mode = GetDlgItem(hwnd, LS_MODE);
	hLS_true = GetDlgItem(hwnd, LS_TRUE);
	hLS_false = GetDlgItem(hwnd, LS_FALSE);
	hLS_act = GetDlgItem(hwnd, LS_ACT);
	hLS_name = GetDlgItem(hwnd, LS_NAME);
	hLS_play_time = GetDlgItem(hwnd, LS_TIME);
	hName = GetDlgItem(hwnd, P_NAME);


	SendMessage(hEasy, BM_SETCHECK, TRUE, 0);

	return TRUE;
}

Game dlg;
Scoreboard score_dlg;
void Math::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case START:
		if (SendMessage(hEasy, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			dlg.dificult = easy;
		}
		if (SendMessage(hHard, BM_GETCHECK, 0, 0) == BST_CHECKED)
		{
			dlg.dificult = hard;
		}

		if (SendMessage(hName, EM_LINELENGTH, 0, 0) == 0)
			MessageBox(hwnd, TEXT("Enter the name"), TEXT("Error"), MB_ICONWARNING);
		else if (SendMessage(hName, EM_LINELENGTH, 0, 0) > 6)
			MessageBox(hwnd, TEXT("Name is too long (have to be 6 or less)"), TEXT("Error"), MB_ICONWARNING);
		else
		{
			SendMessage(hName, WM_GETTEXT, 100, (LPARAM)ls_name);
			/*dlg.act = SendMessage(hAct, CB_GETCURSEL, 0, 0); ///get type of operation(+,-,*,/)*/
			if (dlg.act == -1)
			{
				
				break;
			}
			else
			{
				INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, Game::DlgProc);
				TCHAR sign2[100];
				_itot(ls_true, sign2, 10);
				SetWindowText(hLS_true, sign2);

				_itot(ls_false, sign2, 10);
				SetWindowText(hLS_false, sign2);

				_itot(ls_time, sign2, 10);
				SetWindowText(hLS_play_time, sign2);

				SetWindowText(hLS_mode, ls_mode);
				SetWindowText(hLS_act, ls_act);
				if (finished == true)
				{
					SetWindowText(hLS_name, ls_name);
				}

				
			}
		}

		break;
	case IDC_PLUS:
		dlg.act = 0;
		break;
	case IDC_MINUS:
		dlg.act = 1;
		break;
	case IDC_MULTI:
		dlg.act = 2;
		break;
	case IDC_DIVIDE:
		dlg.act = 3;
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

