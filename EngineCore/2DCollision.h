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
	int CollisionGroup = -1;

public:
	virtual void BeginPlay() override;
	virtual void ComponentTick() override;

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
	template<typename EnumType>
	bool IsCollision(EnumType _OtherCollisionGroup)
	{
		IsCollision(static_cast<int>(_OtherCollisionGroup));
	}
	bool IsCollision(int _OtherCollisionGroup)
	{}

};

