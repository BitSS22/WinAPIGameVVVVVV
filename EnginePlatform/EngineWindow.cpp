
#include "pch.h"
#include "EngineWindow.h"
#include "EngineBase/EngineDebug.h"

HINSTANCE UEngineWindow::hInstance = nullptr;
map<string, WNDCLASSEXA> UEngineWindow::WindowClasss = {};
int WindowCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

UEngineWindow::UEngineWindow()
{
}

UEngineWindow::~UEngineWindow()
{
}


void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;

    WNDCLASSEXA wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEXA);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;

    CreateWindowClass(wcex);
}

void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    if (WindowClasss.contains(_Class.lpszClassName))
        MSGASSERT(nullptr, _Class.lpszClassName, ", 동일한 이름의 Window를 만들 수 없음.");

    RegisterClassExA(&_Class);

    WindowClasss.insert(make_pair(_Class.lpszClassName, _Class));
}

int UEngineWindow::WindowMessageLoop(const EngineDelegate& _StartFuncion, const EngineDelegate& _FrameFunction)
{
    MSG msg = {};

    if (_StartFuncion.IsBind())
    {
        _StartFuncion();
    }

    while (WindowCount > 0)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (_FrameFunction.IsBind())
            _FrameFunction();
    }

    return static_cast<int>(msg.wParam);
}

void UEngineWindow::Create(string_view _TitleName, string_view _ClassName)
{
    if (WindowClasss.contains(_ClassName.data()) == false)
        MSGASSERT(nullptr, _ClassName, ", 동일한 이름의 Window를 만들 수 없음.");

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW
        , 0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (WindowHandle == nullptr)
        MSGASSERT(nullptr, _TitleName, ", Window 생성에 실패 함.");

    BackBuffer = GetDC(WindowHandle);
}

void UEngineWindow::Open(string_view _TitleName)
{
    if (WindowHandle == nullptr)
        Create("Window");

    if (WindowHandle != nullptr)
    {
        ShowWindow(WindowHandle, SW_SHOW);
        UpdateWindow(WindowHandle);
        ++WindowCount;
    }
    else
        MSGASSERT(nullptr, "WindowHandle이 nullptr입니다.");
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        --WindowCount;
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
