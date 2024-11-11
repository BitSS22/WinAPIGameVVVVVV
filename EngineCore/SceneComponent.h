#pragma once
#include "ActorComponent.h"

// Ό³Έν :
class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	~USceneComponent();

	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

private:
	FTransform Transform = {};

public:

private:

public:
	FTransform GetComponentTransform() const
	{
		return Transform;
	}
	FVector2D GetComponentLocation() const
	{
		return Transform.Location;
	}
	FVector2D GetComponentScale() const
	{
		return Transform.Scale;
	}
	FVector2D GetComponentOffsetLocation() const
	{
		return GetActor()->GetActorLocation() + Transform.Location;
	}
	FTransform GetComponentOffsetTransform() const
	{
		return FTransform(GetActor()->GetActorLocation() + Transform.Location, Transform.Scale);
	}
	void SetComponentLocation(FTransform _Transform)
	{
		Transform = _Transform;
	}
	void SetComponentLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}
	void SetComponentScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}
	void AddComponentLocation(FVector2D _Location)
	{
		Transform.Location += _Location;
	}

};

