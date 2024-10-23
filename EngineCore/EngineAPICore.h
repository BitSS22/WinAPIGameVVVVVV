#pragma once
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

// Ό³Έν :
class UEngineAPICore
{
public:
	UEngineAPICore();
	~UEngineAPICore();

	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

private:
	static UEngineAPICore* MainCore;
	UEngineWindow EngineMainWindow = {};

public:
	static int EngineStart(HINSTANCE _Inst);
	UEngineAPICore* GetCore()
	{
		return MainCore;
	}
	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

private:
	static void EngineLoop();

	void Tick();
	void Render();

};

