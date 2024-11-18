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
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite(_Name, 0);
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(_Name);
	if (Sprite->GetSpriteCount() > 2)
	{
		SpriteRenderer->CreateAnimation(Sprite->GetNameView(), Sprite->GetNameView(), 0, Sprite->GetSpriteCount() - 1, EGameConst::AnimationTime, true);
		SpriteRenderer->ChangeAnimation(Sprite->GetNameView());
	}
	SpriteRenderer->SetOrder(ERenderOrder::Entity);

	FVector2D SpriteSize = Sprite->GetSpriteData(0).Transform.Scale;
	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	SetActorScale(SpriteSize);
	SpriteRenderer->SetComponentScale(SpriteSize);


	Collider = CreateDefaultSubObject<U2DCollision>();

	if (_Name.find("PLATFORMS::") != std::string::npos)
		EntityType = EEntityType::Platform;
	else if (_Name.find("SAVE::") != std::string::npos)
		EntityType = EEntityType::Save;
	else
		EntityType = EEntityType::Enermy;

	switch (EntityType)
	{
	case EEntityType::Enermy:
		Collider->SetCollisionGroup(ECollisionGroup::Enermy);
		break;
	case EEntityType::Platform:
		Collider->SetCollisionGroup(ECollisionGroup::Platform);
		break;
	case EEntityType::Save:
		Collider->SetCollisionGroup(ECollisionGroup::Save);
		break;
	}

	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetComponentScale(GetActorScale());
}
