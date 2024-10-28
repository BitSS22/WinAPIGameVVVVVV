#include "pch.h"
#include "V6ContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "PlayGameMode.h"
#include "Player.h"

V6ContentsCore::V6ContentsCore()
{
}

V6ContentsCore::~V6ContentsCore()
{
}

void V6ContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosScale({ 0, 0 }, { 1280, 720 });

	// UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	// UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void V6ContentsCore::Tick()
{
	// UNUSED 현재 사용 하지 않는 함수
}

