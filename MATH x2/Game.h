#pragma once
#include "header.h"

class Game
{
public:
	Game(void);
public:
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT mes, WPARAM wp, LPARAM lp);
	static Game* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnTimer(HWND hwnd, UINT id);
	const int eMin = 1, eMax = 100;
	int chislo1, chislo2,countOfTrue=0,countOfFalse=0;
	HWND hDialog, hFirst, hSecond, hResult, hSign, hNext,hTrue,hFalse,hProgress,hTimeLeft,hImg;
	int act;
	int nCounter;
	const int prStep = 30;
	
	void Plus();
	void Minus();
	void Multiply();
	void Divide();

	bool CheckRes(int val1, int val2, Signs s);
};
