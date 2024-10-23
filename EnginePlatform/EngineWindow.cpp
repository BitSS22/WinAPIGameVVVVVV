
#include "pch.h"
#include "EngineWindow.h"
#include "EngineBase/EngineDebug.h"

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasss = {};
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
        assert(nullptr, (std::string(_Class.lpszClassName) + ", 동일한 이름의 Window를 만들 수 없음.").c_str());

    RegisterClassExA(&_Class);

    WindowClasss.insert(std::make_pair(_Class.lpszClassName, _Class));
}

int UEngineWindow::WindowMessageLoop(const EngineDelegate& _FrameFunction)
{
    MSG msg = {};

    while (WindowCount)
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

void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (WindowClasss.contains(_ClassName.data()) == false)
        assert(nullptr, (std::string(_ClassName.data()) + ", 동일한 이름의 Window를 만들 수 없음.").c_str());

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW
        , 0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (WindowHandle == nullptr)
        assert(nullptr, (std::string(_TitleName.data()) + ", Window 생성에 실패 함.").c_str());
}

void UEngineWindow::Open(std::string_view _TitleName)
{
    if (WindowHandle == nullptr)
        Create("Window");

    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);
    ++WindowCount;
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
