#include "pch.h"
#include "PlayMap.h"

APlayMap::APlayMap()
{
	FVector2D size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();

	SetActorLocation(size);
	SetActorScale(size);
}

APlayMap::~APlayMap()
{
}

