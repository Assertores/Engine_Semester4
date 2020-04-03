#include <stdlib.h>
#include <stdio.h>

#include "rendering/Window.h"

LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(EXIT_SUCCESS);
			break;

		default:
			break;
	}

	return DefWindowProcA(
		hWnd,
		uMsg,
		wParam,
		lParam
	);
}

void Window::Initialize(const char* title, int width, int height)
{
	wWidth = width;
	wHeight = height;

	WNDCLASSEXA wc = { };
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = title;
	wc.lpfnWndProc = WndProc;

	this->className = wc.lpszClassName;

	if (FAILED(RegisterClassEx(&wc)))
	{
		MessageBoxA(NULL, "Failed to register class.", "Error!", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	DWORD style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU;
	this->windowHandle = CreateWindow(
		wc.lpszClassName,
		title,
		style | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		100,
		100,
		width,
		height,
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	if (!this->windowHandle)
	{
		MessageBoxA(NULL, "Failed to create window.", "Error!", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	this->Show(true);
}

Window::~Window()
{
	UnregisterClassA(this->className, GetModuleHandle(NULL));
	DestroyWindow(this->windowHandle);
}

bool Window::PumpMessages()
{
	MSG msg = { };

	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Window::Show(bool show)
{
	ShowWindow(this->windowHandle, show ? SW_SHOW : SW_HIDE);
	UpdateWindow(this->windowHandle);
}