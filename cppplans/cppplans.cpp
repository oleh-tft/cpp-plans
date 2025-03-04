#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "Task.cpp"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hAdd, hDate, hTime, hTags, hComm, hPrio1, hPrio2, hPrio3;
vector<Task> tasks;

Task AddTask(HWND& editDate, HWND& editTime, HWND& editTags, HWND& editComm)
{
    int lengthDate = SendMessage(hDate, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferDate = new TCHAR[lengthDate + 1];
    GetWindowText(hDate, bufferDate, lengthDate + 1);
    int lengthTime = SendMessage(hTime, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferTime = new TCHAR[lengthTime + 1];
    GetWindowText(hTime, bufferTime, lengthTime + 1);
    int lengthTags = SendMessage(hTags, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferTags = new TCHAR[lengthTags + 1];
    GetWindowText(hTags, bufferTags, lengthTags + 1);
    int lengthComm = SendMessage(hComm, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferComm = new TCHAR[lengthComm + 1];
    GetWindowText(hComm, bufferComm, lengthComm + 1);

    int prio = 0;
    if (SendMessage(hPrio1, BM_GETCHECK, 0, 0) == BST_CHECKED) prio = 0;
    else if (SendMessage(hPrio2, BM_GETCHECK, 0, 0) == BST_CHECKED) prio = 1;
    else prio = 2;

    Task newTask(bufferDate, bufferTime, prio, bufferTags, bufferComm);
    tasks.push_back(newTask);
    return newTask;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hAdd = GetDlgItem(hWnd, IDC_BUTTON1);
        hDate = GetDlgItem(hWnd, IDC_EDIT1);
        hTime = GetDlgItem(hWnd, IDC_EDIT2);
        hTags = GetDlgItem(hWnd, IDC_EDIT3);
        hComm = GetDlgItem(hWnd, IDC_EDIT4);
        hPrio1 = GetDlgItem(hWnd, IDC_RADIO1);
        hPrio2 = GetDlgItem(hWnd, IDC_RADIO2);
        hPrio3 = GetDlgItem(hWnd, IDC_RADIO3);
        return TRUE;
    case WM_COMMAND:
        if (wParam == IDC_BUTTON1)
        {
            Task add = AddTask(hDate, hTime, hTags, hComm);
            SendMessage(hList, LB_ADDSTRING, 0, LPARAM(buf));
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}