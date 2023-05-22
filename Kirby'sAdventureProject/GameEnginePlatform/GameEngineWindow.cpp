#include "GameEngineWindow.h"
#include "GameEngineWindowTexture.h"

#include <GameEngineBase/GameEngineDebug.h>


HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = true;
GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
    if (nullptr != WindowBuffer)
    {
        delete WindowBuffer;
        WindowBuffer = nullptr;
    }

    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = nullptr;
    }
}

void GameEngineWindow::ClearBackBuffer()
{
    Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

void GameEngineWindow::DoubleBuffering()
{
    WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
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

    WNDCLASSEXA wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
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

    Hdc = ::GetDC(hWnd);

    // �������� �׸���
    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc);

    // ��ȭ��
    BackBuffer = new GameEngineWindowTexture();
    BackBuffer->ResCreate(WindowBuffer->GetScale());

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SETFOCUS:
    {
        IsFocusValue = true;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_KILLFOCUS:
    {
        IsFocusValue = false;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        IsWindowUpdate = false;
        //PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void GameEngineWindow::MessageLoop(HINSTANCE hInstance, void (*_Start)(HINSTANCE), void (*_Update)(), void (*_End)())
{

    if (nullptr != _Start)
    {
        _Start(hInstance);
    }

    // GetMessage()�� �����忡�� �޼����� ������ �� �޼����� ���ö����� ���Ѵ���Ѵ�.
    // => �޼����� ���ö����� ��� ����
    // �̷��� �޼����� �����Լ���� �Ѵ�.

    // Peekmessgae()�� �޼����� ������ 0�� ���ϵǰ� �ƴϸ� �׳� �����Ѵ�.
    // �׷��� �񵿱� �޼��� �Լ��̴�.


    MSG msg;
    while (IsWindowUpdate)
    {
        // PeekMessage()�� ������ �޼��� ť���� �޼����� ������ �� ����ϰ�, 
        // �޼��� ť�� �޼����� ������ ������� �ʰ� ��� ��ȯ�Ѵ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {// PM_REMOVE�� ����ϸ� �޼����� �������鼭 ť���� ���ŵȴ�.
            if (nullptr != _Update)
            {
                _Update();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // ������ �޼����� ���� �ð��� ����Ÿ���̶�� �ϴµ�, 
        // ������ ����Ÿ�ӿ� ���ư��°� �Ϲ����̴�.
        // ���� �߿� 2���� ������ ������ �ִµ�,
        // �����츦 �����̰ų� â�� ���̸� ȭ���� �����ϴ� ���Ӱ�
        // ������ �޼����� �߻���Ű�¿��߿��� ������ ��� ���ư��� ������ �ִ�.

        // �̷��� �ѹ����� ���� ���� ������(FPS)�̶�� �Ѵ�.
        // FPS�� �ʴ� ȭ���� �׷����� Ƚ���� �ϵ����� ������ �ִ�.
        if (nullptr != _Update)
        {
            _Update();
        }


    }

    if (nullptr != _End)
    {
        _End();
    }

    return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
    Scale = _Scale;

    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = new GameEngineWindowTexture();
        BackBuffer->ResCreate(Scale);
    }

    RECT Rc = { 0,0,_Scale.iX(), _Scale.iY() };

    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}