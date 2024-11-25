#include "pch.h"
#include "Entity.h"
#include "Player.h"

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

void AEntity::Collision(APlayer* _Player)
{
	FTransform PlayerTransform = _Player->GetActorTransform();
	PlayerTransform.Location += _Player->GetMoveValue();

	if (FTransform::Collision(ECollisionType::Rect, PlayerTransform, ECollisionType::Rect, GetActorTransform()) == false)
		return;

	switch (EntityType)
	{
	case EEntityType::CheckPoint:
		CollisionCheckPoint(_Player);
		return;
	case EEntityType::Teleport:
		return;
	}

	MSGASSERT(nullptr, "Not Find Entity Type.");
}

void AEntity::CollisionCheckPoint(APlayer* _Player)
{
	FVector2D PlayerScale = _Player->GetActorScale();
	FVector2D SaveLocation = GetActorLocation();
	string Flip = UEngineString::ToUpper("Flip");

	if (Sprite->GetCurSpriteName().find(Flip) == std::string::npos)
	{
		SaveLocation.Y = GetActorTransform().CenterBottom() - PlayerScale.HalfY();
		_Player->SetCheckPoint(SaveLocation, false);
	}
	else
	{
		SaveLocation.Y = GetActorTransform().CenterTop() + PlayerScale.HalfY();
		_Player->SetCheckPoint(SaveLocation, true);
	}
}

void AEntity::SetEntity(const RoomEntityData& _Data)
{
	EntityType = _Data.EntityType;

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite(_Data.Name, 0);
	Sprite->SetOrder(ERenderOrder::Entity);

	UEngineSprite* NewSprite = UImageManager::GetInst().FindSprite(_Data.Name);
	if (NewSprite->GetSpriteCount() > 1)
	{
		if (_Data.EntityType != EEntityType::PlatformHide)
			Sprite->CreateAnimation(NewSprite->GetNameView(), NewSprite->GetNameView(), 0, NewSprite->GetSpriteCount() - 1, EGameConst::HideTime / (NewSprite->GetSpriteCount() - 1), true);
		else
		{
			Sprite->CreateAnimation(NewSprite->GetNameView(), NewSprite->GetNameView(), 0, NewSprite->GetSpriteCount() - 1, EGameConst::AnimationTime, true);
			Sprite->ChangeAnimation(NewSprite->GetNameView());
		}
	}

	FVector2D SpriteSize = NewSprite->GetSpriteData(0).Transform.Scale;
	SetActorLocation(_Data.DefualtLocation);
	AddActorLocation(_Data.DefualtDir * _Data.MoveLenghtOffset);
	SetActorScale(SpriteSize);
	Sprite->SetComponentScale(SpriteSize);
}

RoomEntityData AEntity::GetEntityData()
{
	RoomEntityData Data = {};

	Data.DefualtLocation = GetActorLocation();
	Data.Name = Sprite->GetCurSpriteName();
	Data.EntityType = EntityType;

	return Data;
}
