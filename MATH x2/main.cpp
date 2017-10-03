#include "header.h"

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpzCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX) };
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	Menu dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), NULL, Menu::DlgProc);
}

