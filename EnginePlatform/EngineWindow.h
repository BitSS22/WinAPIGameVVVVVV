#pragma once
#include <EngineBase/EngineDelegate.h>
#include "EngineWindowImage.h"

class UEngineWindow
{
public:
	UEngineWindow();
	~UEngineWindow();

	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow operator= (const UEngineWindow& _Other) = delete;
	UEngineWindow operator= (UEngineWindow&& _Other) noexcept = delete;

private:
	static HINSTANCE hInstance;
	static map<string, WNDCLASSEXA> WindowClasss;
	HWND WindowHandle = nullptr;
	UEngineWindowImage* BackBufferImage = nullptr;
	UEngineWindowImage* WindowImage = nullptr;

public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	static int WindowMessageLoop(const EngineDelegate& _StartFuncion, const EngineDelegate& _FrameFunction);
	void Create(string_view _TitleName, string_view _ClassName = "Default");
	void Open(string_view _TitleName = "Window");
	void SetWindowPosScale(FVector2D _Pos, FVector2D _Scale);

private:

public:
	void SetWindowTitle(string_view Text)
	{
		SetWindowTextA(WindowHandle, Text.data());
	}
	HDC GetWindowMainDC() const
	{
		return WindowImage->GetDC();
	}

};