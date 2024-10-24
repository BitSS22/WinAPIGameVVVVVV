#include "pch.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
	Levels.clear();
}

int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();

	EngineDelegate Start = EngineDelegate(bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(bind(EngineTick));

	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
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
}

