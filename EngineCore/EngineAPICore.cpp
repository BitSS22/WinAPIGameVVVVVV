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

	EngineDelegate Start = EngineDelegate(bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(bind(EngineTick));

	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

void UEngineAPICore::OpenLevel(string_view _LevelName)
{
	string ChangeName = _LevelName.data();

	auto iter = Levels.find(ChangeName);

	if (iter == Levels.end())
		MSGASSERT(nullptr, ChangeName, ", 레벨이 없음.");

	CurLevel = iter->second;
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	UserCore->Tick();
	MainCore->Tick();
}

void UEngineAPICore::Tick()
{
	if (CurLevel == nullptr)
		MSGASSERT(nullptr, "현재 Level이 지정 되지 않음.");

	CurLevel->Tick();
	CurLevel->Render();
}

