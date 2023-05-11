#include "Application.h"

#include <Windows.h>

Application* Application::application = nullptr;

Application* Application::GetInstance(void)
{
	if (Application::application == nullptr)
		Application::application = new Application();

	return Application::application;
}

void Application::Release(void)
{
	delete Application::application;
	Application::application = nullptr;
}

Application::Application()
{
	this->hWnd = 0;
	this->ptResolution = { };
	this->hDc = 0;

	this->memDc = 0;
	this->hBit = { };
}
Application::~Application()
{
	ReleaseDC(this->hWnd, this->hDc);

	DeleteDC(this->memDc);
	DeleteObject(this->hBit);
}

int Application::init(HWND _hWnd, POINT _ptResolution)
{
	this->hWnd = _hWnd;
	this->ptResolution = _ptResolution;

	RECT rt{ 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(this->hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	this->hDc = GetDC(this->hWnd);

	// double buffering
	this->hBit = CreateCompatibleBitmap(this->hDc, this->ptResolution.x, this->ptResolution.y);
	this->memDc = CreateCompatibleDC(this->hDc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(this->memDc, this->hBit);
	DeleteObject(hOldBit);

	return S_OK;
}

void Application::progress(void)
{
	// Draw
	// update(), render();
	// GetAsyncKeyState(VK_LEFT) & 0x8000

	// COLORREF color = RGB(255, 0, 0);

	/*for (int i = 10; i <= 1280 - 10; i++) {
		for (int j = 10; j <= 768 - 10; j++) {
			SetPixel(this->hDc, i, j, color);
		}
	}*/

	this->update();
	this->render();
}

void Application::update(void)
{

	Application* application = Application::GetInstance();

	/*
	if (GetAsyncKeyState(VK_UP) & 0x8001)
	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	if (GetAsyncKeyState(0x57) & 0x8001) // w
	if (GetAsyncKeyState(0x53) & 0x8001) // s
	*/
}

void Application::render(void)
{
	// clear memDc
	Rectangle(this->memDc, -1, -1, this->ptResolution.x + 1, this->ptResolution.y + 1);


	// ===== RENDER =====



	// ==================
	

	// copy render hDc
	BitBlt(this->hDc, 0, 0, this->ptResolution.x, this->ptResolution.y, this->memDc, 0, 0, SRCCOPY);
}
/*
void Application::drawLine(float sx, float sy, float ex, float ey)
{
	MoveToEx(this->memDc, sx, sy, NULL);
	LineTo(this->memDc, ex, ey);
}

void Application::fillTriangle(POINT p1, POINT p2, POINT p3)
{
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hOldBrush = SelectBrush(this->memDc, hBrush);

	POINT vertices[] = { p1, p2, p3 };
	Polygon(this->memDc, vertices, sizeof(vertices) / sizeof(vertices[0]));

	SelectBrush(this->memDc, hOldBrush);
	DeleteObject(hBrush);
}
*/