#define _CRT_SECURE_NO_WARNINGS
#include "Question.h"

Question* Question::ptr = NULL;
Math dlg_m;
TCHAR timeLeft[100];

Question::Question(void)
{
	ptr = this;
}

void Question::Cls_OnClose(HWND hwnd)
{
	if (nCounter != 0)
	{
		KillTimer(hwnd, 1);
		if (MessageBox(hwnd, TEXT("Exit the game?"), TEXT("Exit"), MB_YESNO) == IDYES)
		{
			EndDialog(hwnd, 0);
			nCounter = prStep;
			curSec = 0;
			/*m_dlg.finished = false;*/
		}
		else
		{
			SetTimer(hDialog, 1, 1000, 0);
		}
	}
	else
		EndDialog(hwnd, 0);
}

BOOL Question::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hArg1 = GetDlgItem(hwnd, ARG1);
	hArg2 = GetDlgItem(hwnd, ARG2);
	hArg3 = GetDlgItem(hwnd, ARG3);
	hNext = GetDlgItem(hwnd, IDC_NEXT);
	hAns1 = GetDlgItem(hwnd, ANS1);
	hAns2 = GetDlgItem(hwnd, ANS2);
	hAns3 = GetDlgItem(hwnd, ANS3);
	hAns4 = GetDlgItem(hwnd, ANS4);
	hSign = GetDlgItem(hwnd, SIGN);
	hTrue = GetDlgItem(hwnd, TRUE_COUNT);
	hFalse = GetDlgItem(hwnd, FALSE_COUNT);
	hProgress = GetDlgItem(hwnd, IDC_PROGRESS1);
	hTimeLeft = GetDlgItem(hwnd, TIME_LEFT);
	hSecNotif = GetDlgItem(hwnd, IDC_SEC_NOTIF);
	SendMessage(hArg1, EM_SETREADONLY, TRUE, 0);
	SendMessage(hArg2, EM_SETREADONLY, TRUE, 0);
	SendMessage(hArg3, EM_SETREADONLY, TRUE, 0);

	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, prStep));
	SendMessage(hProgress, PBM_SETSTEP, (WPARAM)1, 0);
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 250, 0)));
	/*SendMessage(hProgress, PBS_SMOOTH, 0, 0);*/
	SetTimer(hDialog, 1, 1000, 0);
	nCounter = prStep;
	total_play_time = prStep;
	curSec = 0;

	countOfTrue = 0;
	countOfFalse = 0;

	DecideFirst();
	return TRUE;
}
int chooseArg;
void Question::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_NEXT)
	{
		bool check = true;
		TCHAR sign[100];

		if (SendMessage(hCurArg, EM_LINELENGTH, 0, 0) == 0) //првоерка пустое ли поле ответа
		{
			return;
		}
		else
		{
			SetCounts();
			if (checkForNext == true)
				AddThreeSec();

			chooseArg = rand() % (2 - 1 + 1) + 1;

			if (chooseArg == 1)
				DecideFirst();
			else if (chooseArg == 2)
				DecideSecond();
		}

	}
	else if (id == ANS1)
	{
		CheckButtonRes(hAns1);
		SetFocus(hNext);
	}
	else if (id == ANS2)
	{
		CheckButtonRes(hAns2);
		SetFocus(hNext);
	}
	else if (id == ANS3)
	{
		CheckButtonRes(hAns3);
		SetFocus(hNext);
	}
	else if (id == ANS4)
	{
		CheckButtonRes(hAns4);
		SetFocus(hNext);
	}
}

void Question::Cls_OnTimer(HWND hwnd, UINT id)
{
	if (id == 1)
	{
		/*m_dlg.finished = true;*/
		nCounter--;
		curSec++;

		if (nCounter == 5)
		{
			SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 0, 0)));
		}
		_itot(nCounter, timeLeft, 10);
		SetWindowText(hTimeLeft, timeLeft);
		SendMessage(hProgress, PBM_STEPIT, 0, 0); 

		if (nCounter == 0)
		{
			KillTimer(hwnd, 1);
			SendMessage(hProgress, PBM_SETSTEP, 0, 0); 
			SetWindowText(hwnd, TEXT("GAME OVER"));
			EnableWindow(hNext, FALSE);
			SetWindowText(hArg1, TEXT(""));
			SetWindowText(hArg2, TEXT(""));
			SetWindowText(hArg3, TEXT(""));
			SetWindowText(hAns1, TEXT(""));
			SetWindowText(hAns2, TEXT(""));
			SetWindowText(hAns3, TEXT(""));
			SetWindowText(hAns4, TEXT(""));

			SaveScore();

		}
	}
	if (id == 2)
	{
		bonus++;
		if (bonus == 1)
		{
			KillTimer(hDialog, 2);
			SendMessage(hSecNotif, WM_SETTEXT, 0, LPARAM(TEXT("")));
			bonus = 0;
		}
	}
}

	BOOL CALLBACK Question::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{

		switch (message)
		{
			HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
			HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
			HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
			HANDLE_MSG(hwnd, WM_TIMER, ptr->Cls_OnTimer);
		}
		return FALSE;
	}
	PName name;
	void Question::SaveScore()
	{
		wfstream fout("scoreboard2.txt", ios::out | ios::app);
		fout.imbue(std::locale(""));
		fout << "  ";
		fout << name.p_name;
		fout << "\t\t";
		fout << countOfTrue;
		fout << "\t\t";
		fout << countOfFalse;
		fout << "\n";
		fout.close();
	}

	void Question::AddThreeSec()
	{
		SecAnim();
		nCounter += 3;
		total_play_time += 3;
		curSec -= 3;
		_itot(nCounter, timeLeft, 10);
		SetWindowText(hTimeLeft, timeLeft);
		SendMessage(hProgress, PBM_SETPOS, curSec, 0);

	}
	void Question::SecAnim()
	{
		SendMessage(hSecNotif, WM_SETTEXT, 0, LPARAM(TEXT("+3 sec")));
		SetTimer(hDialog, 2, 1000, 0);

	}

	void Question::CheckButtonRes(HWND button)
	{
		TCHAR resT[50];
		int resI;
		GetWindowText(button, resT, 50);
		SetWindowText(hCurArg, resT);
		resI = _ttoi(resT);

		if (resI == trueRes)
		{
			checkForNext = true;
			countOfTrue++;
		}
		else
		{
			checkForNext = false;
			countOfFalse++;
		}
		
	}

	void Question::SetCounts()
	{
		TCHAR tr[50];
		TCHAR fl[50];
		_itot(countOfTrue, tr, 50);
		_itot(countOfFalse, fl, 50);

		SetWindowText(hTrue, tr);
		SetWindowText(hFalse, fl);
	}

	void Question::SetButtonsValues()
	{
		int random,rand1,rand2,rand3;
		TCHAR temp[50];
		if (hCurArg == hArg1 || hCurArg == hArg3)
		{
			rand1 = rand() % (trueRes - 1 + 1) + 1;
			rand1 = rand1 + 3;

			rand2 = rand() % (trueRes - 1 + 1) + 1;
			rand2 = rand2 + rand2 / 2;

			rand3 = rand() % (trueRes - 1 + 1) + 1;
			rand3 = trueRes + rand3;
		}
		else
		{
			
			rand1 = trueRes +2;

			
			rand2 = trueRes + 1;

			
			rand3 = trueRes + 5;
		}

		random = rand() % (4 - 1 + 1) + 1;
		if (random == 1)
		{
			_itot(trueRes, temp, 10);
			SetWindowText(hAns1, temp);

			_itot(rand1, temp, 10);
			SetWindowText(hAns2, temp);

			_itot(rand2, temp, 10);
			SetWindowText(hAns3, temp);

			_itot(rand3, temp, 10);
			SetWindowText(hAns4, temp);
		}
		else if (random == 2)
		{
			_itot(trueRes, temp, 10);
			SetWindowText(hAns2, temp);

			_itot(rand1, temp, 10);
			SetWindowText(hAns3, temp);

			_itot(rand2, temp, 10);
			SetWindowText(hAns1, temp);

			_itot(rand3, temp, 10);
			SetWindowText(hAns4, temp);
		}
		else if (random == 3)
		{
			_itot(trueRes, temp, 10);
			SetWindowText(hAns3, temp);

			_itot(rand1, temp, 10);
			SetWindowText(hAns2, temp);

			_itot(rand2, temp, 10);
			SetWindowText(hAns4, temp);

			_itot(rand3, temp, 10);
			SetWindowText(hAns1, temp);
		}
		else if (random == 4)
		{
			_itot(trueRes, temp, 10);
			SetWindowText(hAns4, temp);

			_itot(rand1, temp, 10);
			SetWindowText(hAns1, temp);

			_itot(rand2, temp, 10);
			SetWindowText(hAns3, temp);

			_itot(rand3, temp, 10);
			SetWindowText(hAns2, temp);
		}
	}

	void Question::DecideFirst()
	{
		SendMessage(hArg1, WM_SETTEXT, 0, (LPARAM)TEXT(""));
		hCurArg = hArg1;

		RandomSign();

		srand(time(NULL));
		TCHAR tchislo[100];

		if (sign == PLUS)
			PlusForFirst();
		else if (sign == MINUS)
			MinusForFirst();
		else if (sign == MULT)
			MultForFirst();
		else if (sign == DIVIDE)
			DivideForFirst();
		SetButtonsValues();

	}

	void Question::RandomSign()
	{
		srand(time(NULL));
		sign = rand() % (3 - 0 + 1) + 0;

		if (sign == PLUS)
			SetWindowText(hSign, TEXT("+"));
		else if (sign == MINUS)
			SetWindowText(hSign, TEXT("-"));
		else if (sign == MULT)
			SetWindowText(hSign, TEXT("*"));
		else if (sign == DIVIDE)
			SetWindowText(hSign, TEXT("/"));

	}

	void Question::PlusForFirst()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg1 = rand() % (50 - 1 + 1) + 1;


		arg2 = rand() % (50 - 1 + 1) + 1;
		_itot(arg2, tchislo, 10);
		SetWindowText(hArg2, tchislo);

		arg3 = arg1 + arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg1;
	}

	void Question::MinusForFirst()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg1 = rand() % (50 - 1 + 1) + 1;


		arg2 = rand() % (arg1 - 1 + 1) + 1;
		_itot(arg2, tchislo, 10);
		SetWindowText(hArg2, tchislo);

		arg3 = arg1 - arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg1;
	}

	void Question::MultForFirst()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg1 = rand() % (10 - 2 + 1) + 2;


		arg2 = rand() % (9 - 2 + 1) + 2;;
		_itot(arg2, tchislo, 10);
		SetWindowText(hArg2, tchislo);

		arg3 = arg1 * arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg1;
	}

	void Question::DivideForFirst()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg2 = rand() % (4 - 2 + 1) + 2;
		_itot(arg2, tchislo, 10);
		SetWindowText(hArg2, tchislo);
		if (arg2 % 2 == 0)
		{
			do
			{
				arg1 = rand() % (50 - 1 + 1) + 1;
			} while (arg1 % 2 != 0 || arg1 % arg2 != 0);

		}
		else
		{
			do
			{
				arg1 = rand() % (50 - 1 + 1) + 1;
			} while (arg1 % 2 == 0 || arg1 % arg2 != 0);
		}

		arg3 = arg1 / arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg1;
	}



	////////second


	void Question::DecideSecond()
	{
		SendMessage(hArg2, WM_SETTEXT, 0, (LPARAM)TEXT(""));
		hCurArg = hArg2;

		RandomSign();

		srand(time(NULL));
		TCHAR tchislo[100];

		if (sign == PLUS)
			PlusForSecond();
		else if (sign == MINUS)
			MinusForSecond();
		else if (sign == MULT)
			MultForSecond();
		else if (sign == DIVIDE)
			DivideForSecond();
		SetButtonsValues();

	}

	

	void Question::PlusForSecond()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg1 = rand() % (50 - 1 + 1) + 1;
		_itot(arg1, tchislo, 10);
		SetWindowText(hArg1, tchislo);

		arg2 = rand() % (50 - 1 + 1) + 1;


		arg3 = arg1 + arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg2;
	}

	void Question::MinusForSecond()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg1 = rand() % (50 - 1 + 1) + 1;
		_itot(arg1, tchislo, 10);
		SetWindowText(hArg1, tchislo);

		arg2 = rand() % (arg1 - 1 + 1) + 1;

		arg3 = arg1 - arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg2;
	}

	void Question::MultForSecond()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg1 = rand() % (10 - 2 + 1) + 2;
		_itot(arg1, tchislo, 10);
		SetWindowText(hArg1, tchislo);

		arg2 = rand() % (9 - 2 + 1) + 2;;


		arg3 = arg1 * arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg2;
	}

	void Question::DivideForSecond()
	{
		srand(time(NULL));
		TCHAR tchislo[100];

		arg2 = rand() % (4 - 2 + 1) + 2;

		if (arg2 % 2 == 0)
		{
			do
			{
				arg1 = rand() % (50 - 1 + 1) + 1;
			} while (arg1 % 2 != 0 || arg1 % arg2 != 0);


		}
		else
		{
			do
			{
				arg1 = rand() % (50 - 1 + 1) + 1;
			} while (arg1 % 2 == 0 || arg1 % arg2 != 0);
		}
		_itot(arg1, tchislo, 10);
		SetWindowText(hArg1, tchislo);

		arg3 = arg1 / arg2;
		_itot(arg3, tchislo, 10);
		SetWindowText(hArg3, tchislo);
		trueRes = arg2;
	}
