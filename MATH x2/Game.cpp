#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

Game* Game::ptr = NULL;
Math m_dlg;
TCHAR timeL[100];
Game::Game(void)
{
	ptr = this;
}

bool Game::CheckRes(int val1,int val2,Signs s)
{
	int trueRes=0,ourRes;
	TCHAR str[100];
	if (s == PLUS)
	{
		trueRes = val1 + val2;
	}
	else if (s == MINUS)
	{
		trueRes = val1 - val2;
	}
	else if (s == MULT)
	{
		trueRes = val1 * val2;
	}
	else if (s == DIVIDE)
	{
		trueRes = val1 / val2;
	}
	GetWindowText(hResult, str, 100);
	ourRes = _ttoi(str);

	if (ourRes == trueRes)
		return true;
	else
		return false;
}

void Game::ePlus()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (eMax - eMin + 1) + eMin;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (20 - eMin + 1) + eMin;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);

	SetWindowText(hSign, TEXT("+"));
}
void Game::eMinus()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (eMax - eMin + 1) + eMin;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (chislo1 - eMin + 1) + eMin;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);


	SetWindowText(hSign, TEXT("-"));
}

void Game::eMultiply()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (20 - 2 + 1) + 2;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (9 - 2 + 1) + 2;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);


	SetWindowText(hSign, TEXT("*"));
}
void Game::eDivide()
{
	srand(time(NULL));
	TCHAR tchislo[100];

	chislo2 = rand() % (4 - 2 + 1) + 2;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);
	if (chislo2 % 2 == 0)
	{
		do
		{
			chislo1 = rand() % (eMax/2 - eMin + 1) + eMin;
		} while (chislo1 % 2 != 0 || chislo1 % chislo2 != 0);
		
	}
	else
	{
		do
		{
			chislo1 = rand() % (eMax/2 - eMin + 1) + eMin;
		} while (chislo1 % 2 == 0 || chislo1 % chislo2 !=0);
	}
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	SetWindowText(hSign, TEXT("/"));
}

void Game::haPlus()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (haMax - haMin + 1) + haMin;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (haMax - haMin + 1) + haMin;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);

	SetWindowText(hSign, TEXT("+"));
}
void Game::haMinus()
{	
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (haMax - haMin + 1) + haMin;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (chislo1 - haMin + 1) + haMin;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);


	SetWindowText(hSign, TEXT("-"));
}
void Game::haMultiply()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (eMax - 2 + 1) + 2;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (9 - 2 + 1) + 2;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);


	SetWindowText(hSign, TEXT("*"));
}

void Game::haDivide()
{
	srand(time(NULL));
	TCHAR tchislo[100];

	chislo2 = rand() % (4 - 2 + 1) + 2;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);
	if (chislo2 % 2 == 0)
	{
		do
		{
			chislo1 = rand() % (eMax - eMin + 1) + eMin;
		} while (chislo1 % 2 != 0 || chislo1 % chislo2 != 0);

	}
	else
	{
		do
		{
			chislo1 = rand() % (eMax - eMin + 1) + eMin;
		} while (chislo1 % 2 == 0 || chislo1 % chislo2 != 0);
	}
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	SetWindowText(hSign, TEXT("/"));
}
void Game::AddTwoSec()
{
	SecAnim();
	nCounter += 2;
	total_play_time += 2;
	curSec -= 2;
	_itot(nCounter, timeL, 10);
	SetWindowText(hTimeLeft, timeL);
	SendMessage(hProgress, PBM_SETPOS, curSec, 0);
	
}
void Game::SecAnim()
{
	SendMessage(hSecNotif, WM_SETTEXT, 0, LPARAM(TEXT("+2 sec")));
	SetTimer(hDialog, 2, 1000, 0);
	
}

void Game::Cls_OnClose(HWND hwnd)
{
	if (nCounter != 0)
	{
		KillTimer(hwnd, 1);
		if (MessageBox(hwnd, TEXT("Exit the game?"), TEXT("Exit"), MB_YESNO) == IDYES)
		{
			EndDialog(hwnd, 0);
			nCounter = prStep;
			curSec = 0;
		}
		else
		{
			SetTimer(hDialog, 1, 1000, 0);
		}
	}
	else
		EndDialog(hwnd, 0);
}

HBITMAP bitImg;
HINSTANCE hInst;

BOOL Game::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hFirst = GetDlgItem(hwnd, FIRST);
	hSecond = GetDlgItem(hwnd, SECOND);
	hResult = GetDlgItem(hwnd, RESULT);
	hSign = GetDlgItem(hwnd, IDC_SIGN);
	hNext = GetDlgItem(hwnd, NEXT);
	hTrue = GetDlgItem(hwnd, TRUE_COUNT);
	hFalse = GetDlgItem(hwnd, FALSE_COUNT);
	hProgress = GetDlgItem(hwnd, PROGRESS);
	hTimeLeft = GetDlgItem(hwnd, TIME_LEFT);
	hSecNotif = GetDlgItem(hwnd, TWO_SEC);

	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, prStep));
	SendMessage(hProgress, PBM_SETSTEP, (WPARAM)1,0);
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 255, 0)));
	/*SendMessage(hProgress, PBS_SMOOTH, 0, 0);*/
	SetTimer(hDialog, 1, 1000, 0);
	nCounter = prStep;
	total_play_time = prStep;
	curSec = 0;

	countOfTrue = 0;
	countOfFalse = 0;

	//hInst = GetModuleHandle(0);
	//bitImg = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	//SendMessage(hImg, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitImg); //отрисовать

	
	if (dificult == easy)
	{
		if (act == PLUS)
			ePlus();
		else if (act == MINUS)
			eMinus();
		else if (act == MULT)
			eMultiply();
		else if (act == DIVIDE)
			eDivide();
	}
	else if (dificult == hard)
	{
		if (act == PLUS)
			haPlus();
		else if (act == MINUS)
			haMinus();
		else if (act == MULT)
			haMultiply();
		else if (act == DIVIDE)
			haDivide();
	}

	return TRUE;
}
void Game::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
		if (id == NEXT)
		{
			bool check = true;
			TCHAR sign[100];

			if (SendMessage(hResult, EM_LINELENGTH, 0, 0) == 0) //првоерка пустое ли поле ответа
			{
				return;
			}
			else
			{

				if (act == PLUS)
				{
					if (check == CheckRes(chislo1, chislo2, PLUS))
					{
						countOfTrue++;
						_itot(countOfTrue, sign, 10);
						SetWindowText(hTrue, sign);
						AddTwoSec();
					}
					else
					{
						countOfFalse++;
						_itot(countOfFalse, sign, 10);
						SetWindowText(hFalse, sign);
					}
					if (dificult == easy)
						ePlus();
					else if (dificult == hard)
						haPlus();
				}
				else if (act == MINUS)
				{
					if (check == CheckRes(chislo1, chislo2, MINUS))
					{
						countOfTrue++;
						_itot(countOfTrue, sign, 10);
						SetWindowText(hTrue, sign);
						AddTwoSec();
					}
					else
					{
						countOfFalse++;
						_itot(countOfFalse, sign, 10);
						SetWindowText(hFalse, sign);
					}
					if (dificult == easy)
						eMinus();
					else if (dificult == hard)
						haMinus();
				}
				else if (act == MULT)
				{
					if (check == CheckRes(chislo1, chislo2, MULT))
					{
						countOfTrue++;
						_itot(countOfTrue, sign, 10);
						SetWindowText(hTrue, sign);
						AddTwoSec();
					}
					else
					{
						countOfFalse++;
						_itot(countOfFalse, sign, 10);
						SetWindowText(hFalse, sign);
					}
					if (dificult == easy)
						eMultiply();
					else if (dificult == hard)
						haMultiply();
				}
				else if (act == DIVIDE)
				{
					if (check == CheckRes(chislo1, chislo2, DIVIDE))
					{
						countOfTrue++;
						_itot(countOfTrue, sign, 10);
						SetWindowText(hTrue, sign);
						AddTwoSec();
					}
					else
					{
						countOfFalse++;
						_itot(countOfFalse, sign, 10);
						SetWindowText(hFalse, sign);
					}
					if (dificult == easy)
						eDivide();
					else if (dificult == hard)
						haDivide();
				}
				SetWindowText(hResult, TEXT(""));
			}
		}
		
}
u_int bonus = 0;
void Game::Cls_OnTimer(HWND hwnd, UINT id)
{
	if (id == 1)
	{
		SetFocus(hResult);
		nCounter--;
		curSec++;

		if (nCounter == 5)
		{
			SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 0, 0)));
		}
		_itot(nCounter, timeL, 10);
		SetWindowText(hTimeLeft, timeL);
		SendMessage(hProgress, PBM_STEPIT, 0, 0); // »зменение текущей позиции индикатора путЄм прибавлени€ шага

		if (nCounter == 0)
		{
			KillTimer(hwnd, 1);
			SendMessage(hProgress, PBM_SETSTEP, 0, 0); // ”становка шага приращени€  индикатора 
			/*Button_Enable(hStart, FALSE);*/
			SetWindowText(hwnd, TEXT("GAME OVER"));
			EnableWindow(hNext, FALSE);
			EnableWindow(hResult, FALSE);
			SetWindowText(hFirst, TEXT(""));
			SetWindowText(hSecond, TEXT(""));

			m_dlg.ls_true = countOfTrue;
			m_dlg.ls_false = countOfFalse;
			m_dlg.ls_time = total_play_time;

			if (dificult == easy)
			{
				_tcscpy(m_dlg.ls_mode, TEXT("Easy"));

			}
			else if (dificult == hard)
			{
				_tcscpy(m_dlg.ls_mode, TEXT("Hard"));

			}
			if (act == PLUS)
				_tcscpy(m_dlg.ls_act, TEXT("Plus"));
			else if (act == MINUS)
				_tcscpy(m_dlg.ls_act, TEXT("Minus"));
			else if (act == MULT)
				_tcscpy(m_dlg.ls_act, TEXT("Multiply"));
			else if (act == DIVIDE)
				_tcscpy(m_dlg.ls_act, TEXT("Divide"));

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

BOOL CALLBACK Game::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
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

void Game::SaveScore()
{
	wfstream fout("scoreboard.txt", ios::out | ios::app);
	fout.imbue(std::locale(""));
	fout << "  ";
	fout << m_dlg.ls_name;
	fout << "\t\t";
	fout << m_dlg.ls_act;
	fout << "\t\t";
	fout << m_dlg.ls_mode;
	fout << "\t\t";
	fout << m_dlg.ls_true;
	fout << "\t\t";
	fout << m_dlg.ls_false;
	fout << "\n";
	fout.close();
}