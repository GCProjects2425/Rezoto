#include <Windows.h>

#define ID_BUTTON_CREATE 1
#define ID_BUTTON_VIEW 2

class GameServerGUI {
public:
    GameServerGUI(HINSTANCE hInstance) : hInstance(hInstance), hwnd(NULL), hwndLog(NULL) {}

    void Run() {
        RegisterWindowClass();
        CreateAppWindow();
        MessageLoop();
    }

private:
    HINSTANCE hInstance;
    HWND hwnd;
    HWND hwndLog;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        GameServerGUI* self;
        if (uMsg == WM_NCCREATE) {
            self = static_cast<GameServerGUI*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
        }
        else {
            self = reinterpret_cast<GameServerGUI*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (self) {
            return self->HandleMessage(hwnd, uMsg, wParam, lParam);
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void RegisterWindowClass();
    void CreateAppWindow();
    void MessageLoop();

    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};