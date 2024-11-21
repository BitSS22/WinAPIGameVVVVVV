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

void AEntity::Collision()
{
	AActor* Actor = Collider->CollisionOnce(ECollisionGroup::Player);
	APlayer* Player = dynamic_cast<APlayer*>(Actor);

	if (Player == nullptr)
		return;

 	switch (EntityType)
	{
	case EEntityType::Guy:
		return;
	case EEntityType::Enermy:
		Player->SetDeath(true);
		return;
	case EEntityType::Platform:
		return;
	case EEntityType::CheckPoint:
		CollisionCheckPoint(Player);
		return;
	case EEntityType::Teleport:
		return;
	}

	MSGASSERT(nullptr, "Not Find Entity Type.");

	// TODO. Entity Collision Code Create
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
