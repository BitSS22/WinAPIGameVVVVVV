#include "pch.h"
#include "Entity.h"

AEntity::AEntity()
{
}

AEntity::~AEntity()
{
}

void AEntity::Tick()
{
	Super::Tick();

	// Debug
	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);
}

void AEntity::SetEntity(const RoomEntityData& _Data)
{
	EntityType = _Data.EntityType;

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite(_Data.Name, 0);
	Sprite->SetOrder(ERenderOrder::Entity);

	UEngineSprite* NewSprite = UImageManager::GetInst().FindSprite(_Data.Name);
	if (NewSprite->GetSpriteCount() > 2)
	{
		Sprite->CreateAnimation(NewSprite->GetNameView(), NewSprite->GetNameView(), 0, NewSprite->GetSpriteCount() - 1, EGameConst::AnimationTime, true);
		Sprite->ChangeAnimation(NewSprite->GetNameView());
	}

	FVector2D SpriteSize = NewSprite->GetSpriteData(0).Transform.Scale;
	SetActorLocation(_Data.DefualtLocation);
	AddActorLocation(_Data.DefualtDir * _Data.MoveLenghtOffset);
	SetActorScale(SpriteSize);
	Sprite->SetComponentScale(SpriteSize);
	
	Collider = CreateDefaultSubObject<U2DCollision>();
	Collider->SetCollisionGroup(ECollisionGroup::Entity);
	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetComponentScale(GetActorScale());
}

RoomEntityData AEntity::GetEntityData()
{
	RoomEntityData Data = {};

	Data.DefualtLocation = GetActorLocation();
	Data.Name = Sprite->GetCurSpriteName();
	Data.EntityType = EntityType;

	return Data;
}
