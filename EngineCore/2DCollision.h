#pragma once
#include <set>
#include "SceneComponent.h"
#include <EngineCore/Level.h>
#include <EngineCore/Actor.h>

class U2DCollision : public USceneComponent
{
public:
	friend class ULevel;
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

	std::set<U2DCollision*> CollisionCheckSet = {};
	std::function<void(AActor*)> Enter = {};
	std::function<void(AActor*)> Stay = {};
	std::function<void(AActor*)> End = {};

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
	std::vector<AActor*> CollisionAll(EnumType _OtherCollisionGroup, FVector2D _NextDir)
	{
		std::vector<AActor*> Result = {};
		Collision(static_cast<int>(_OtherCollisionGroup), Result, _NextDir, -1);

		return Result;
	}

private:
	void CollisionEventCheck(U2DCollision* _Other);

public:
	template<typename EnumType>
	EnumType GetCollisionGroup()
	{
		return static_cast<EnumType>(CollisionGroup);
	}
	int GetCollisionGroup() const
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
	ECollisionType GetCollisionType() const
	{
		return CollisionType;
	}

	void SetCollisionEnter(std::function<void(AActor*)> _Function);
	void SetCollisionStay(std::function<void(AActor*)> _Function);
	void SetCollisionEnd(std::function<void(AActor*)> _Function);

};

