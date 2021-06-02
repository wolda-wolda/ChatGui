#include <windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include "client.h"

#define SETTINGS_MENU_EXIT 1
#define CONNECT 2
#define SEND 3
#define RECEIVE 4


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hwnd);

void AddControls(HWND hwnd);

void AddSend(HWND hwnd);

void AddConnect(HWND hwnd);

HMENU hMenu;
HWND hEdit;
HWND hButton;
HWND hButton2;
HWND hWrite;
HFONT hFont;

SOCKET client = 0;
time_t zeit;
int beenden = 0;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) {
        return -1;
    } else {
        HWND hwnd = CreateWindowW(L"myWindowClass", L"C Chat", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
                                  NULL, NULL,
                                  NULL, NULL);
        MSG msg = {0};
        while (GetMessage(&msg, NULL, NULL, NULL)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (client != 0) {
                SendMessage(hwnd, WM_COMMAND, RECEIVE, 0);
            }
        }
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    char text[100];
    char *buf = malloc(10000);
    memset(buf, '\0', 10000);

    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case SETTINGS_MENU_EXIT:
                    DestroyWindow(hwnd);
                    break;
                case CONNECT:
                    EnableWindow(hButton, false);
                    client = sock(text);
                    strcat(buf, text);
                    SetWindowText(hEdit, buf);
                    if (strcmp(buf, "Verbindung fehlgeschlagen\r\n") != 0) {
                        DestroyWindow(hButton);
                        printf("Hier");
                        Sleep(1000);
                        AddSend(hwnd);
                    } else {
                        SetWindowText(hEdit, buf);
                        EnableWindow(hButton, true);
                    }
                    break;
                case SEND:
                    GetWindowText(hWrite, text, 1000);
                    beenden = sen(text, client, zeit);
                    GetWindowText(hEdit, buf, 10000);
                    strcat(buf, text);
                    SetWindowText(hEdit, buf);
                    SendMessage(hEdit, WM_VSCROLL, SB_BOTTOM, 0);
                    if (beenden == 1) {
                        EnableWindow(hButton2, false);
                        client = 0;
                        beenden = 0;
                        DestroyWindow(hButton2);
                        AddConnect(hwnd);
                        SetWindowText(hWrite, "");
                        SetWindowText(hEdit, "");
                    }
                case RECEIVE:
                    beenden = echo(client, text, zeit);
                    GetWindowText(hEdit, buf, 10000);
                    strcat(buf, text);
                    SetWindowText(hEdit, buf);
                    SendMessage(hEdit, WM_VSCROLL, SB_BOTTOM, 0);
                    if (beenden == 1) {
                        EnableWindow(hButton2, false);
                        client = 0;
                        beenden = 0;
                        DestroyWindow(hButton2);
                        AddConnect(hwnd);
                        SetWindowText(hWrite, "");
                        SetWindowText(hEdit, "");
                    }
                    break;
                default:
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hwnd);
            AddControls(hwnd);
            AddConnect(hwnd);
            break;
        case WM_DESTROY:
            sen("exit",client, zeit);
            PostQuitMessage(0);
            break;
        default:
            DefWindowProcW(hwnd, msg, wp, lp);
            break;
    }
}

void AddMenus(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU hFileSettings = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) hFileSettings, "Einstellungen");
    AppendMenu(hFileSettings, MF_STRING, CONNECT, "Verbinden");
    AppendMenu(hFileSettings, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileSettings, MF_STRING, SETTINGS_MENU_EXIT, "Exit");
    SetMenu(hwnd, hMenu);
}

void AddControls(HWND hwnd) {
    hEdit = CreateWindowW(L"Edit", L"",
                          WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL, 50, 0, 435,
                          385, hwnd,
                          NULL, NULL, NULL);
    hWrite = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                           0, 400,
                           390, 40, hwnd, NULL, NULL, NULL);
    SendMessageW(hEdit, WM_SETFONT, (LPARAM) GetStockObject(DEFAULT_GUI_FONT), true);
    SendMessageW(hWrite, WM_SETFONT, (LPARAM) GetStockObject(DEFAULT_GUI_FONT), true);
}

void AddSend(HWND hwnd) {
    hButton2 = CreateWindowW(L"Button", L"Senden", WS_VISIBLE | WS_CHILD, 390, 400, 93, 40, hwnd, (HMENU) SEND, NULL,
                            NULL);
    SendMessageW(hButton2, WM_SETFONT, (LPARAM) GetStockObject(DEFAULT_GUI_FONT), true);
}

void AddConnect(HWND hwnd) {
    hButton = CreateWindowW(L"Button", L"Verbinden", WS_VISIBLE | WS_CHILD, 390, 400, 93, 40, hwnd, (HMENU) CONNECT,
                            NULL, NULL);
    SendMessageW(hButton, WM_SETFONT, (LPARAM) GetStockObject(DEFAULT_GUI_FONT), true);
}