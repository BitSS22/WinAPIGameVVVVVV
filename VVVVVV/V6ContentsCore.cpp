#include "pch.h"
#include "V6ContentsCore.h"
#include <EngineCore/EngineAPICore.h>

V6ContentsCore::V6ContentsCore()
{
}

V6ContentsCore::~V6ContentsCore()
{
}

void V6ContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("Play");
	UEngineAPICore::GetCore()->CreateLevel("End");
}

void V6ContentsCore::Tick()
{
}

