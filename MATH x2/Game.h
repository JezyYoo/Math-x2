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
	const int eMin = 1, eMax = 100,haMin = 10,haMax = 200;
	int chislo1, chislo2,countOfTrue=0,countOfFalse=0;
	HWND hDialog, hFirst, hSecond, hResult, hSign, hNext,hTrue,hFalse,hProgress,hTimeLeft,hImg,hSecNotif;
	int act,dificult;
	int nCounter;
	const int prStep = 30; // count of seconds
	int curSec;
	int total_play_time;

	void ePlus();
	void eMinus();
	void eMultiply();
	void eDivide();

	void haPlus();
	void haMinus();
	void haMultiply();
	void haDivide();

	bool CheckRes(int val1, int val2, Signs s);

	void SaveScore();
	void AddTwoSec();
	void SecAnim();
};
