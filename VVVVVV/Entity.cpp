#include "pch.h"
#include "Entity.h"

AEntity::AEntity()
{
}

AEntity::~AEntity()
{
}

void AEntity::SetEntity(const AGameWorld::RoomData::RoomEntityData& _Data)
{
	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite(_Data.Name, 0);

	UEngineSprite* NewSprite = UImageManager::GetInst().FindSprite(_Data.Name);
	Sprite->SetOrder(ERenderOrder::Entity);
	if (NewSprite->GetSpriteCount() > 2)
	{
		Sprite->CreateAnimation(NewSprite->GetNameView(), NewSprite->GetNameView(), 0, NewSprite->GetSpriteCount() - 1, EGameConst::AnimationTime, true);
		Sprite->ChangeAnimation(NewSprite->GetNameView());
	}

	FVector2D SpriteSize = NewSprite->GetSpriteData(0).Transform.Scale;
	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	SetActorScale(SpriteSize);
	Sprite->SetComponentScale(SpriteSize);

	Collider = CreateDefaultSubObject<U2DCollision>();
	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetComponentScale(GetActorScale());
}
