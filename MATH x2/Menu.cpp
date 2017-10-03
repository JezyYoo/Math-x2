#include "Menu.h"

Menu* Menu::ptr = NULL;
vector<wstring> Menu::score;
Question dlgg;

Menu::Menu(void)
{
	ptr = this;
}

void Menu::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Menu::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)greenBrush);

	LoadFromFile();
	return TRUE;
}

void Menu::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_EXIT:
		EndDialog(hwnd, 0);
		break;
	case IDC_SCOREBOARD:
		 DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, Scoreboard::DlgProc);
		break;
	case IDC_SIMPLE:
		 DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Math::DlgProc);
		 LoadFromFile();
		break;
	case IDC_QUESTION:
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG5), hwnd, Question::DlgProc);
		break;
	}

	
}

BOOL CALLBACK Menu::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}

void Menu::LoadFromFile()
{
	if (score.size() != 0)
	{
		score.clear();
	}
	TCHAR buff[100]; 
	wfstream fin("scoreboard.txt"); 
	fin.imbue(std::locale(""));

	while (!fin.eof())
	{
		fin.getline(buff, 100); 
		wstring str = buff;
		score.push_back(str);
	}
	fin.close(); 

}