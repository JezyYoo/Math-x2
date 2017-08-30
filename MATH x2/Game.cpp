#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

Game* Game::ptr = NULL;

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

void Game::Plus()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (eMax - eMin + 1) + eMin;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (eMax - eMin + 1) + eMin;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);

	SetWindowText(hSign, TEXT("+"));
}
void Game::Minus()
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

void Game::Multiply()
{
	srand(time(NULL));
	TCHAR tchislo[100];
	chislo1 = rand() % (eMax - eMin + 1) + eMin;
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	chislo2 = rand() % (9 - 1 + 1) + 1;
	_itot(chislo2, tchislo, 10);
	SetWindowText(hSecond, tchislo);


	SetWindowText(hSign, TEXT("*"));
}
void Game::Divide()
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
		} while (chislo1 % 2 != 0);
		
	}
	else
	{
		do
		{
			chislo1 = rand() % (eMax - eMin + 1) + eMin;
		} while (chislo1 % 2 == 0);
	}
	_itot(chislo1, tchislo, 10);
	SetWindowText(hFirst, tchislo);

	


	SetWindowText(hSign, TEXT("/"));
}

void Game::Cls_OnClose(HWND hwnd)
{
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

	SendMessage(hProgress, PBM_SETRANGE, 0, MAKELPARAM(0, prStep));
	SendMessage(hProgress, PBM_SETSTEP, (WPARAM)1,0);
	SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(0, 255, 0)));
	SetTimer(hDialog, 1, 1000, 0);
	nCounter = prStep;

	countOfTrue = 0;
	countOfFalse = 0;

	hInst = GetModuleHandle(0);
	bitImg = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	SendMessage(hImg, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitImg); //отрисовать

	

	if (act == PLUS)
		Plus();
	else if (act == MINUS)
		Minus();
	else if (act == MULT)
		Multiply();
	else if (act == DIVIDE)
		Divide();


	return TRUE;
}
void Game::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == NEXT)
	{
		bool check = true;
		TCHAR sign[100];

		if (SendMessage(hResult, EM_LINELENGTH, 0, 0) == 0)
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
				}
				else
				{
					countOfFalse++;
					_itot(countOfFalse, sign, 10);
					SetWindowText(hFalse, sign);
				}

				Plus();
			}
			else if (act == MINUS)
			{
				if (check == CheckRes(chislo1, chislo2, MINUS))
				{
					countOfTrue++;
					_itot(countOfTrue, sign, 10);
					SetWindowText(hTrue, sign);
				}
				else
				{
					countOfFalse++;
					_itot(countOfFalse, sign, 10);
					SetWindowText(hFalse, sign);
				}
				Minus();
			}
			else if (act == MULT)
			{
				if (check == CheckRes(chislo1, chislo2, MULT))
				{
					countOfTrue++;
					_itot(countOfTrue, sign, 10);
					SetWindowText(hTrue, sign);
				}
				else
				{
					countOfFalse++;
					_itot(countOfFalse, sign, 10);
					SetWindowText(hFalse, sign);
				}
				Multiply();
			}
			else if (act == DIVIDE)
			{
				if (check == CheckRes(chislo1, chislo2, DIVIDE))
				{
					countOfTrue++;
					_itot(countOfTrue, sign, 10);
					SetWindowText(hTrue, sign);
				}
				else
				{
					countOfFalse++;
					_itot(countOfFalse, sign, 10);
					SetWindowText(hFalse, sign);
				}
				Divide();
			}
			SetWindowText(hResult, TEXT(""));
		}
	}

}
TCHAR timeL[100];
void Game::Cls_OnTimer(HWND hwnd, UINT id)
{
	SetFocus(hResult);
	nCounter-- ;

	if (nCounter == 5)
	{
		SendMessage(hProgress, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 0, 0)));
	}
	_itot(nCounter, timeL, 10);
	SetWindowText(hTimeLeft, timeL);
	SendMessage(hProgress, PBM_STEPIT, 0, 0); // Изменение текущей позиции индикатора путём прибавления шага

	if (nCounter == 0)
	{
		KillTimer(hwnd, 1);
		SendMessage(hProgress, PBM_SETSTEP, 0, 0); // Установка шага приращения  индикатора 
		/*Button_Enable(hStart, FALSE);*/
		SetWindowText(hwnd, TEXT("GAME OVER"));
		EnableWindow(hNext, FALSE);
		EnableWindow(hResult, FALSE); 
		SetWindowText(hFirst, TEXT(""));
		SetWindowText(hSecond, TEXT(""));
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