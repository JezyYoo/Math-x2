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
	HWND hDialog,hEasy,hMid,hHard,hLS_mode,hLS_true,hLS_false,hLS_act,hName,hLS_name,hLS_play_time;
	HWND hPlus, hMinus, hDivide, hMulti;
	static TCHAR ls_mode[100],ls_act[100],ls_name[100];
	static int ls_true, ls_false,ls_time;
	static bool finished;

};
