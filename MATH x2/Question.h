#pragma once
#include "header.h"



class Question
{
public:
	Question(void);
public:
	static BOOL CALLBACK DlgProc(HWND hwnd, UINT mes, WPARAM wp, LPARAM lp);
	static Question* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnTimer(HWND hwnd, UINT id);
	HWND hDialog,hArg1,hArg2,hArg3,hNext,hAns1,hAns2,hAns3,hAns4,hSign,hTrue,hFalse,hProgress,hTimeLeft,hSecNotif;
	HWND hCurArg;
	int arg1, arg2, arg3;
	u_int bonus = 0;
	int sign;
	int trueRes;
	int nCounter;
	const int prStep = 30;
	int curSec;
	int total_play_time;
	bool checkForNext = false;
	int countOfTrue = 0;
	int countOfFalse = 0;

	void DecideFirst();
	void PlusForFirst();
	void MinusForFirst();
	void MultForFirst();
	void DivideForFirst();

	void DecideSecond();
	void PlusForSecond();
	void MinusForSecond();
	void MultForSecond();
	void DivideForSecond();


	void RandomSign();
	void SetButtonsValues();
	void CheckButtonRes(HWND button);
	void SetCounts();

	void AddThreeSec();
	void SecAnim();

};
