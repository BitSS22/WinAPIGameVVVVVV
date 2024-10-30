#include "pch.h"
#include "PlayMap.h"

APlayMap::APlayMap()
{

	FVector2D size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation(size.Half());
	SetActorScale(size);

	SetSprite("VVVVVV_2.4_title_screen.png");
}

APlayMap::~APlayMap()
{
}

