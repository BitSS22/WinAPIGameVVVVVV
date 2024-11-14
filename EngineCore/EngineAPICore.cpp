#include "pch.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
}

UEngineAPICore::~UEngineAPICore()
{
	auto iter = Levels.begin();

	while (iter != Levels.end())
	{
		delete iter->second;
		++iter;
	}
	Levels.clear();
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	UEngineDelegate Start = UEngineDelegate(bind(EngineBeginPlay));
	UEngineDelegate FrameLoop = UEngineDelegate(bind(EngineTick));

	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

void UEngineAPICore::OpenLevel(string_view _LevelName)
{
	string UpperName = UEngineString::ToUpper(_LevelName);

	auto iter = Levels.find(UpperName);

	if (iter == Levels.end())
		MSGASSERT(nullptr, _LevelName, "이라는 이름의 레벨이 없습니다.");

	NextLevel = iter->second;
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	// UNUSED 현재 사용 하지 않는 함수
	// UserCore->Tick();
	MainCore->Tick();
}

void UEngineAPICore::LevelChange()
{
	if (IsCurLevelReset == true)
	{
		delete CurLevel;
		CurLevel = nullptr;
		IsCurLevelReset = false;
	}

	if (NextLevel != nullptr)
	{
		if (CurLevel != nullptr)
			CurLevel->LevelChangeEnd();

		CurLevel = NextLevel;

		NextLevel->LevelChangeStart();
		NextLevel = nullptr;

		DeltaTimer.TimeStart();
	}
}

void UEngineAPICore::Tick()
{
	LevelChange();

	DeltaTimer.TimeCheck();

	UEngineInput::GetInst().KeyCheck();
	UEngineInput::GetInst().EventCheck();

	if (CurLevel == nullptr)
		MSGASSERT(nullptr, "현재 Level이 지정 되지 않음.");
	else
	{
		CurLevel->Tick();
		CurLevel->Render();
		CurLevel->Collision();
		CurLevel->Realease();
	}
}

