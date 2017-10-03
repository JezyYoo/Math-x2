#pragma once
#include "header.h"



class Menu
{
public:
	Menu(void);
public:
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT mes, WPARAM wp, LPARAM lp);
	static Menu* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hDialog,hSimple,hQuestion,hGuide,hScore,hExit;
	static void LoadFromFile();
	static vector<wstring> score;
};
