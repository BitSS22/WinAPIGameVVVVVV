#pragma once
#include "Enums.h"
#include "EngineCore/Actor.h"
#include "GameWorld.h"

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

protected:

public:
	virtual void SetEntity(const AGameWorld::RoomData::RoomEntityData& _Data) = 0;

private:

public:
	void SetEntityType(EEntityType _Type)
	{
		EntityType = _Type;
	}
	EEntityType GetEntityType()
	{
		return EntityType;
	}
	USpriteRenderer* GetSpriteRenderer()
	{
		return Sprite;
	}
	U2DCollision* GetCollision()
	{
		return Collider;
	}
	ARoom* GetRoom()
	{
		return Room;
	}

};

