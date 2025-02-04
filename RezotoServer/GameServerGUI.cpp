#include <iostream>
#include "GameServerGUI.h"
#include "GameManager.h"

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
    hwndListBox = CreateWindowA("LISTBOX", "", WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
        200, 50, 250, 150, hwnd, (HMENU)ID_LISTBOX, NULL, NULL);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    SetTimer(hwnd, 1, 1000, NULL);
}

void GameServerGUI::MessageLoop() {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void GameServerGUI::UpdateListBox()
{
    SendMessage(hwndListBox, LB_RESETCONTENT, 0, 0);
    if (GameManager* manager = GameManager::GetInstance())
    {
        const GameManager::PartyList& partyList = manager->GetPartyList();
        if (partyList.empty()) return;

        for (const Party& p : partyList)
        {
            char buffer[50];
            sprintf_s(buffer, "Party %d | 2/4 players", p.GetID());
            SendMessageA(hwndListBox, LB_ADDSTRING, 0, (LPARAM)buffer);
        }
    }
}

LRESULT GameServerGUI::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_BUTTON_CREATE:
        {
            if (GameManager* manager = GameManager::GetInstance())
            {
                int ID = manager->CreateParty();
                if (ID > 0)
                {
                    std::string log = "New party created : ";
                    //logQueue.push(log);
                    std::cout << log << ID << std::endl;  // Log dans la console
                    UpdateListBox();
                }
                else
                {
                    std::cout << "Max party reached (20)." << std::endl;
                }
            }
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
