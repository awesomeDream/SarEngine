#pragma once

#include <Windows.h>

class Application
{
private:
	static Application* application;

public:
	static Application* GetInstance(void);
	static void Release(void);

private:
	HWND hWnd;			// Main Window Handler
	POINT ptResolution;	// Main Window Resolution (ÇØ»óµµ)
	HDC hDc;			// Main Window Draw DC

	HBITMAP hBit;
	HDC memDc;

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress(void);
	void update(void);
	void render(void);

public:
	void drawLine(float sx, float sy, float ex, float ey) const;

private:
	Application();
	~Application();
};
