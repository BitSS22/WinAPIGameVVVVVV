#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class U2DCollision : public USceneComponent
{
public:
	U2DCollision();
	~U2DCollision();

	U2DCollision(const U2DCollision& _Other) = delete;
	U2DCollision(U2DCollision&& _Other) noexcept = delete;
	U2DCollision& operator=(const U2DCollision& _Other) = delete;
	U2DCollision& operator=(U2DCollision&& _Other) noexcept = delete;

private:
	ECollisionType CollisionType = ECollisionType::Circle;
	int CollisionGroup = -1;

public:
	virtual void BeginPlay() override;
	virtual void ComponentTick() override;

	bool Collision(int _OtherCollisionGroup, std::vector<AActor*>& _Result, FVector2D _NextPos, UINT _Limit);
	
	template<typename EnumType>
	AActor* CollisionOnce(EnumType _OtherCollisionGroup, FVector2D _NextPos = FVector2D::ZERO)
	{
		std::vector<AActor*> Result = {};
		Collision(static_cast<int>(_OtherCollisionGroup), Result, _NextPos, 1);

		if (Result.empty() == true)
			return nullptr;

		return Result[0];
	}

	template<typename EnumType>
	std::vector<AActor*> CollisionAll(EnumType _OtherCollisionGroup)
	{
		std::vector<AActor*> Result = {};
		Collision(static_cast<int>(_OtherCollisionGroup), Result, -1);

		return Result;
	}

private:

public:
	template<typename EnumType>
	EnumType GetCollisionGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}
	int GetCollisionGroup()
	{
		return CollisionGroup;
	}

	template<typename EnumType>
	void SetCollisionGroup(EnumType _CollisionGroup)
	{
		CollisionGroup = static_cast<int>(_CollisionGroup);
	}
	void SetCollisionGroup(int _CollisionGroup)
	{
		CollisionGroup = _CollisionGroup;
	}

	void SetCollisionType(ECollisionType _Type)
	{
		CollisionType = _Type;
	}

};

