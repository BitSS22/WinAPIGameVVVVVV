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
	ULevel* NextLevel = nullptr;
	UEngineTimer DeltaTimer = {};
	UEngineRandom Random = {};
	bool IsCurLevelReset = false;

public:
	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);
	void OpenLevel(string_view _LevelName);

	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);

		if (Levels.contains(UpperName) == true)
			MSGASSERT(nullptr, _LevelName, "이라는 이름의 Level은 이미 존재합니다.");

		ULevel* NewLevel = new ULevel();
		NewLevel->CreateGameMode<GameModeType, MainPawnType>();
		NewLevel->SetName(UpperName);
		Levels.insert(make_pair(UpperName, NewLevel));

		return NewLevel;
	}
	template<typename GameModeType, typename MainPawnType>
	void ResetLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);

		if (CurLevel->GetName() != UpperName)
		{
			DestroyLevel(_LevelName);
			CreateLevel<GameModeType, MainPawnType>(_LevelName);
			return;
		}

		auto iter = Levels.find(UpperName);
		Level.erase(iter);
		NextLevel = CreateLevel<GameModeType, MainPawnType>(UpperName);
		IsCurLevelReset = true;
	}

	void DestroyLevel(std::string_view _LevelName)
	{
		std::string UpperName = UEngineString::ToUpper(_LevelName);

		if (Levels.contains(UpperName) == false)
			return;

		auto iter = Levels.find(UpperName);

		if (iter->second != nullptr)
		{
			delete iter->second;
			iter->second = nullptr;
		}

		Levels.erase(iter);
	}

private:
	static void EngineBeginPlay();
	static void EngineTick();
	void LevelChange();

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
	UEngineRandom& GetRandomDevice()
	{
		return Random;
	}

};

