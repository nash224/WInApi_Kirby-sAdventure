#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
}

void GameEngineWindow::Open(const std::string& _Title, HINSTANCE hInstance)
{
    Instance = hInstance;
    Title = _Title;

    if (nullptr == Instance)
    {
        MsgBoxAssert("Hinstance ���� �����츦 �����Ϸ��� �߽��ϴ�.");
    }

    MyRegisterClass();
    InitInstance();
}


void GameEngineWindow::MyRegisterClass()
{

    static bool Check = false;

    if (true == Check)
    {
        return;
    }

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow";
    wcex.hIconSm = nullptr;


    // �Լ��� ���еǸ�(������Ű�� ���������� �������� ���ϸ�) ��ȯ���� 0
    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("������ Ŭ������ ����ϴµ� �����߽��ϴ�.");
        return;
    }

    Check = true;

}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void GameEngineWindow::InitInstance()
{
    hWnd = CreateWindowA(
        "DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("������ ������ �����߽��ϴ�.");
        return;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

void GameEngineWindow::MessageLoop(HINSTANCE hInstance, void (*_Start)(HINSTANCE), void (*_Update)(), void (*_End)())
{

    if (nullptr != _Start)
    {
        _Start(hInstance);
    }


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (nullptr != _Update)
        {
            _Update();
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (nullptr != _End)
    {
        _End();
    }

    return;
}