#include "pch.h"
#include "Entity.h"

AEntity::AEntity()
{
}

AEntity::~AEntity()
{
}

void AEntity::BeginPlay()
{
}

void AEntity::EntityDefaultSetUp(std::string_view _Name)
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite(_Name, 0);
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(_Name);
	Renderer->CreateAnimation(Sprite->GetNameView(), Sprite->GetNameView(), 0, Sprite->GetSpriteCount(), EGameConst::AnimationTime, true);
	Renderer->ChangeAnimation(Sprite->GetNameView());

	FVector2D SpriteSize = Sprite->GetSpriteData(0).Transform.Scale;
	SetActorScale(SpriteSize);
	Renderer->SetComponentScale(SpriteSize);
}
