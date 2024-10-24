#pragma once
#include <EnginePlatform/EngineWindow.h>
#include "Level.h"

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

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
	static UContentsCore* UserCore;
	UEngineWindow EngineMainWindow = {};
	map<string, ULevel*> Levels = {};

public:
	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);
	void CreateLevel(string_view _LevelName);
	
private:
	static void EngineBeginPlay();
	static void EngineTick();

	void Tick();

public:
	static class UEngineAPICore* GetCore()
	{
		return MainCore;
	}
	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

};

