#pragma once
#include "Enums.h"
#include "EngineCore/Actor.h"

class AGameWorld;
class ARoom;

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
	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* Collider = nullptr;
	EEntityType EntityType = EEntityType::Last;

protected:

public:
	virtual void SetEntity(std::string_view _Name) = 0;

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

};

