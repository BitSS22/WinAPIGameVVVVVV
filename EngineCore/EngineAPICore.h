#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <EnginePlatform/EngineWindow.h>
#include "Level.h"
#include <EngineBase/EngineTimer.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

using std::string;
using std::string_view;
using std::map;

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
	ULevel* CurLevel = nullptr;
	UEngineTimer DeltaTimer = {};

public:
	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);
	void OpenLevel(string_view _LevelName);

	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(string_view _LevelName)
	{
		ULevel* NewLevel = new ULevel();
		NewLevel->CreateGameMode<GameModeType, MainPawnType>();
		Levels.insert(make_pair(_LevelName, NewLevel));

		return NewLevel;
	}
	
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
	float GetDeltaTime()
	{
		return DeltaTimer.GetDeltaTime();
	}
	UINT GetFrame()
	{
		return DeltaTimer.GetFrame();
	}

};

