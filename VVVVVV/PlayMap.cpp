#include "pch.h"
#include "PlayMap.h"

APlayMap::APlayMap()
{
	FVector2D size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation(size.Half());
	SetActorScale(size);
	 
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("VVVVVV_2.4_title_screen.png");
	SpriteRenderer->SetComponentLocation({0, 0});
	SpriteRenderer->SetComponentScale(size);
}

APlayMap::~APlayMap()
{
}

