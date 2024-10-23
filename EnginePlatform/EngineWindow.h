#pragma once
#include <EngineBase/EngineDelegate.h>

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
	static std::map<std::string, WNDCLASSEXA> WindowClasss;
	HWND WindowHandle = nullptr;

public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	static int WindowMessageLoop(const EngineDelegate& _FrameFunction);

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");

private:

};