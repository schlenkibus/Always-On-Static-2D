#include "Application.h"
#include <Windows.h>
#include "Tools/createNoiseImage.h"

int main() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

    auto& app = Application::get();
    return app.run();
}