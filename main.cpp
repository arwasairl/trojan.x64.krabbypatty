#include <iostream>
#include <Windows.h>
#include "payloads.h"
HWND hWnd;

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
			switch (q2Res) {
			case IDYES:
				MessageBox(NULL, L"FUCK YOU!!", L"YOU SUCK", MB_ICONERROR);
				OverrideWallpaper();
				showDialog();
				break;
			case IDNO:
				MessageBox(NULL, L"Oh... Well I'll make sure you're ready :)", L"Matte Kudasai!!!", MB_ICONINFORMATION);
				break;
			}
			break;
		}
	}
	else {
		return 1;
	}
	return 0;
}