#pragma once
#include "header.h"

class Math
{
public:
	Math(void);
public:
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT mes, WPARAM wp, LPARAM lp);
	static Math* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hDialog,hEasy,hMid,hHard,hAct;
};
