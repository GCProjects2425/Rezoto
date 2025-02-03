#include <iostream>
#include "GameServerGUI.h"

void GameServerGUI::RegisterWindowClass() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"GameServerUI";
    RegisterClass(&wc);
}

void GameServerGUI::CreateAppWindow() {
    hwnd = CreateWindowExA(0, "GameServerUI", "Gestion du Serveur", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 300,
        NULL, NULL, hInstance, this);

    if (!hwnd) {
        std::cerr << "Erreur lors de la création de la fenêtre." << std::endl;
        return;
    }

    // Création des éléments UI
    CreateWindowA("BUTTON", "Créer Partie", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 50, 150, 30, hwnd, (HMENU)ID_BUTTON_CREATE, NULL, NULL);
    CreateWindowA("BUTTON", "Voir Infos", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        20, 100, 150, 30, hwnd, (HMENU)ID_BUTTON_VIEW, NULL, NULL);
    hwndLog = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
        200, 50, 250, 150, hwnd, NULL, NULL, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    SetTimer(hwnd, 1, 1000, NULL); // Mise à jour des logs toutes les secondes
}

void GameServerGUI::MessageLoop() {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT GameServerGUI::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BUTTON_CREATE:
        {
            //std::lock_guard<std::mutex> lock(logMutex);
            std::string log = "Nouvelle partie créée !";
            //logQueue.push(log);
            std::cout << log << std::endl;  // Log dans la console
        }
        break;
        case ID_BUTTON_VIEW:
            MessageBoxA(hwnd, "Affichage des infos de partie...", "Info", MB_OK);
            break;
        }
        break;

    case WM_TIMER:
    {
        //std::lock_guard<std::mutex> lock(logMutex);
        std::string logs;
        /*while (!logQueue.empty()) {
            logs += logQueue.front() + "\r\n";
            logQueue.pop();
        }
        SetWindowText(hwndLog, logs.c_str());*/
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
