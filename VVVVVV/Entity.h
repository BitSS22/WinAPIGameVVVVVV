#pragma once
#include "Enums.h"
#include "EngineCore/Actor.h"
#include "GameWorld.h"
#include "Room.h"
#include <EngineCore/EngineSprite.h>
#include <EngineCore/2DCollision.h>

class APlayer;

class AEntity : public AActor
{
public:
	AEntity();
	~AEntity();

	AEntity(const AEntity& _Other) = delete;
	AEntity(AEntity&& _Other) noexcept = delete;
	AEntity& operator=(const AEntity& _Other) = delete;
	AEntity& operator=(AEntity&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	U2DCollision* Collider = nullptr;
	EEntityType EntityType = EEntityType::Last;
	ARoom* Room = nullptr;
	bool IsMove = true;

protected:

public:
	virtual void Tick() override;

	virtual void Collision(APlayer* _Player);
	void CollisionCheckPoint(APlayer* _Player);

	virtual void SetEntity(const RoomEntityData& _Data);
	virtual RoomEntityData GetEntityData();

private:

public:
	EEntityType GetEntityType() const
	{
		return EntityType;
	}
	std::string GetSpriteName() const
	{
		return Sprite->GetCurSpriteName();
	}
	U2DCollision* GetCollision() const
	{
		return Collider;
	}
	void SetRoom(ARoom* _Room)
	{
		Room = _Room;
	}
	ARoom* GetRoom() const
	{
		return Room;
	}
	virtual void AddEntityLocation(const FVector2D& _Location)
	{
		AddActorLocation(_Location);
	}
	virtual FVector2D GetEntityLocation() const
	{
		return GetActorLocation();
	}
	void SetIsMove(bool _Value)
	{
		IsMove = _Value;
	}
	bool GetIsMove() const
	{
		return IsMove;
	}

};

