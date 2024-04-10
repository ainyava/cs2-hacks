#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>

#include "memory/memory.hpp"
#include "classes/vector.hpp"
#include "hacks/reader.hpp"
#include "hacks/hack.hpp"
#include "classes/globals.hpp"
#include "classes/render.hpp"

bool finish = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		g::hdcBuffer = CreateCompatibleDC(NULL);
		g::hbmBuffer = CreateCompatibleBitmap(GetDC(hWnd), g::gameBounds.right, g::gameBounds.bottom);
		SelectObject(g::hdcBuffer, g::hbmBuffer);

		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

		SetLayeredWindowAttributes(hWnd, RGB(255, 255, 255), 0, LWA_COLORKEY);

		std::cout << "[overlay] Window created successfully" << std::endl;
		Beep(500, 100);
		break;
	}
	case WM_ERASEBKGND: // We handle this message to avoid flickering
		return TRUE;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//DOUBLE BUFFERING
		FillRect(g::hdcBuffer, &ps.rcPaint, (HBRUSH)GetStockObject(WHITE_BRUSH));


		if (GetForegroundWindow() == g_game.process->hwnd_) {
			//render::RenderText(g::hdcBuffer, 10, 10, "cs2 | ESP", RGB(75, 175, 175), 15);
			hack::loop();
		}

		BitBlt(hdc, 0, 0, g::gameBounds.right, g::gameBounds.bottom, g::hdcBuffer, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case WM_DESTROY:
		DeleteDC(g::hdcBuffer);
		DeleteObject(g::hbmBuffer);

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void read_thread() {
	while (!finish) {
		g_game.loop();
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
}

int main() {
	
	std::cout << "[info] Github Repository: https://github.com/ainyava/cs2-hacks" << std::endl;

	std::cout << "[config] Reading configuration." << std::endl;

	g_game.init();

	std::cout << "[overlay] Waiting to focus game to create the overlay..." << std::endl;
	std::cout << "[overlay] Make sure your game is in \"Full Screen Windowed\"" << std::endl;
	while (GetForegroundWindow() != g_game.process->hwnd_) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		g_game.process->UpdateHWND();
		ShowWindow(g_game.process->hwnd_, TRUE);
	}
	std::cout << "[overlay] Creating window overlay..." << std::endl;

	WNDCLASSEXA wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hbrBackground = WHITE_BRUSH;
	wc.hInstance = reinterpret_cast<HINSTANCE>(GetWindowLongA(g_game.process->hwnd_, (-6))); // GWL_HINSTANCE));
	wc.lpszMenuName = " ";
	wc.lpszClassName = " ";

	RegisterClassExA(&wc);

	GetClientRect(g_game.process->hwnd_, &g::gameBounds);

	// Create the window
	HINSTANCE hInstance = NULL;
	HWND hWnd = CreateWindowExA(WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW, " ", "cs2-external-esp", WS_POPUP,
		g::gameBounds.left, g::gameBounds.top, g::gameBounds.right - g::gameBounds.left, g::gameBounds.bottom + g::gameBounds.left, NULL, NULL, hInstance, NULL); // NULL, NULL);

	if (hWnd == NULL)
		return 0;

	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	ShowWindow(hWnd, TRUE);
	//SetActiveWindow(hack::process->hwnd_);

	// Launch game memory reading thread
	std::thread read(read_thread);
	std::cout << "\n[settings] In Game keybinds:\n\t[F4] enable/disable Box ESP\n\t[F5] enable/disable Team ESP\n\t[F7] enable/disable extra flags\n\t[F8] enable/disable skeleton esp\n\t[F9] enable/disable head tracker\n\t[end] Unload esp.\n" << std::endl;
	std::cout << "[settings] Make sure you check the config for additional settings!" << std::endl;

	// Message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) && !finish)
	{
		if (GetAsyncKeyState(VK_END) & 0x8000) finish = true;

		if (GetAsyncKeyState(VK_F4) & 0x8000) { config::show_box_esp = !config::show_box_esp; Beep(700, 100); };

		if (GetAsyncKeyState(VK_F5) & 0x8000) { config::team_esp = !config::team_esp; Beep(700, 100); };

		if (GetAsyncKeyState(VK_F7) & 0x8000) { config::show_extra_flags = !config::show_extra_flags; Beep(700, 100); };

		if (GetAsyncKeyState(VK_F8) & 0x8000) { config::show_skeleton_esp = !config::show_skeleton_esp; Beep(700, 100); };

		if (GetAsyncKeyState(VK_F9) & 0x8000) { config::show_head_tracker = !config::show_head_tracker; Beep(700, 100); };

		TranslateMessage(&msg);
		DispatchMessage(&msg);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	read.detach();

	Beep(700, 100); Beep(700, 100);

	std::cout << "[overlay] Destroying overlay window." << std::endl;
	DeleteDC(g::hdcBuffer);
	DeleteObject(g::hbmBuffer);

	DestroyWindow(hWnd);

	g_game.close();

#ifdef NDEBUG
	std::cout << "[cs2] Press any key to close" << std::endl;
	std::cin.get();
#endif

	return 1;
}
