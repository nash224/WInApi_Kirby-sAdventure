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
        MsgBoxAssert("Hinstance 없이 윈도우를 생성하려고 했습니다.");
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


    // 함수가 실패되면(윈도우키를 정상적으로 생성하지 못하면) 반환값은 0
    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("윈도우 클래스를 등록하는데 실패했습니다.");
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
        MsgBoxAssert("윈도우 생성에 실패했습니다.");
        return;
    }

    Hdc = ::GetDC(hWnd);

    // 윈도우의 그림판
    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc);

    // 도화지
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

    // GetMessage()는 스레드에서 메세지를 가져올 때 메세지가 들어올때까지 무한대기한다.
    // => 메세지가 들어올때까지 계속 정지
    // 이러한 메세지를 동기함수라고 한다.

    // Peekmessgae()는 메세지가 없으면 0이 리턴되고 아니면 그냥 리턴한다.
    // 그래서 비동기 메세지 함수이다.


    MSG msg;
    while (IsWindowUpdate)
    {
        // PeekMessage()는 윈도우 메세지 큐에서 메세지를 가져올 때 사용하고, 
        // 메세지 큐에 메세지가 없으면 대기하지 않고 즉시 반환한다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {// PM_REMOVE를 사용하면 메세지를 가져오면서 큐에서 제거된다.
            if (nullptr != _Update)
            {
                _Update();
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        // 윈도우 메세지가 없는 시간을 데드타임이라고 하는데, 
        // 게임은 데드타임에 돌아가는게 일반적이다.
        // 게임 중에 2가지 종류의 게임이 있는데,
        // 윈도우를 움직이거나 창을 줄이면 화면이 정지하는 게임과
        // 윈도우 메세지를 발생시키는와중에도 게임이 계속 돌아가는 게임이 있다.

        // 이렇게 한바퀴가 도는 것을 프레임(FPS)이라고 한다.
        // FPS는 초당 화면이 그려지는 횟수로 하드웨어와 연관이 있다.
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