#pragma once
#include <Windows.h>

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
	HWND WindowHandle = nullptr;

public:
	static int WindowMessageLoop();
	static void EngineWindowInit(HINSTANCE _Instance);
	void Open();

private:

};