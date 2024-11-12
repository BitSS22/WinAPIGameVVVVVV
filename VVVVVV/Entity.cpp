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
	Super::BeginPlay();
}

void AEntity::EntityDefaultSetUp(std::string_view _Name, FVector2D _Location)
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetSprite(_Name, 0);
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(_Name);
	Renderer->CreateAnimation(Sprite->GetNameView(), Sprite->GetNameView(), 0, Sprite->GetSpriteCount() - 1, EGameConst::AnimationTime, true);
	Renderer->ChangeAnimation(Sprite->GetNameView());
	Renderer->SetOrder(ERenderOrder::Entity);

	FVector2D SpriteSize = Sprite->GetSpriteData(0).Transform.Scale;
	SetActorLocation(_Location);
	SetActorScale(SpriteSize);
	Renderer->SetComponentScale(SpriteSize);
}
