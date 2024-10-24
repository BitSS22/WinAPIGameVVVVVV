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
	// UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	// UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void V6ContentsCore::Tick()
{
}

