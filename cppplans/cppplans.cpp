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
HWND hList, hTaskDate, hTaskTime, hTaskPrio, hTaskTags, hTaskComm;
HWND hFind, hFindButton, hSave;
vector<Task> tasks;

void ShowAll()
{
    SendMessage(hList, LB_RESETCONTENT, 0, 0);
    for (Task task : tasks)
    {
        SendMessage(hList, LB_ADDSTRING, 0, LPARAM(task.GetCommentary()));
    }
}

void FindTask()
{
    SendMessage(hList, LB_RESETCONTENT, 0, 0);

    int lengthFind = SendMessage(hFind, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferFind = new TCHAR[lengthFind + 1];
    GetWindowText(hFind, bufferFind, lengthFind + 1);

    vector<Task> filtered;
    for (Task task : tasks)
    {
        if (_tcsstr(task.GetDate(), bufferFind) != nullptr || _tcsstr(task.GetTime(), bufferFind) != nullptr ||
            _tcsstr(task.GetTags(), bufferFind) != nullptr || _tcsstr(task.GetCommentary(), bufferFind) != nullptr ||
            _tcsstr(task.GetPriority(), bufferFind) != nullptr)
        {
            filtered.push_back(task);
        }
    }
    
    for (Task task : filtered)
    {
        SendMessage(hList, LB_ADDSTRING, 0, LPARAM(task.GetCommentary()));
    }
}

Task AddTask()
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
        hList = GetDlgItem(hWnd, IDC_LIST1);
        hTaskDate = GetDlgItem(hWnd, IDC_EDIT5);
        hTaskTime = GetDlgItem(hWnd, IDC_EDIT6);
        hTaskPrio = GetDlgItem(hWnd, IDC_EDIT7);
        hTaskTags = GetDlgItem(hWnd, IDC_EDIT8);
        hTaskComm = GetDlgItem(hWnd, IDC_EDIT9);
        hFind = GetDlgItem(hWnd, IDC_EDIT10);
        hFindButton = GetDlgItem(hWnd, IDC_BUTTON2);
        hSave = GetDlgItem(hWnd, IDC_BUTTON3);

        return TRUE;
    case WM_COMMAND:
        if (wParam == IDC_BUTTON1)
        {
            Task add = AddTask();
            SendMessage(hList, LB_ADDSTRING, 0, LPARAM(add.GetCommentary()));
        }
        if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE)
        {
            int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
            if (index != LB_ERR)
            {
                Task currentTask;
                for (int i = 0; i < tasks.size(); i++)
                {
                    int length = SendMessage(hList, LB_GETTEXTLEN, index, 0);
                    TCHAR* pBuffer = new TCHAR[length + 1];
                    SendMessage(hList, LB_GETTEXT, index, LPARAM(pBuffer));
                    if (_tcscmp(pBuffer, tasks.at(i).GetCommentary()) == 0)
                    {
                        currentTask = tasks.at(i);
                        break;
                    }
                }
                SetWindowText(hTaskDate, currentTask.GetDate());
                SetWindowText(hTaskTime, currentTask.GetTime());
                SetWindowText(hTaskPrio, currentTask.GetPriority());
                SetWindowText(hTaskTags, currentTask.GetTags());
                SetWindowText(hTaskComm, currentTask.GetCommentary());
            }
        }
        if (wParam == IDC_BUTTON2)
        {
            FindTask();
        }
        if (wParam == IDC_BUTTON3)
        {
            for (Task task : tasks)
            {
                task.SaveToFile();
            }
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}