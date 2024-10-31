#pragma once
#include "ActorComponent.h"

// ���� :
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
	FTransform GetActorTransform() const
	{
		FVector2D ActorLocation = GetActor()->GetTransform().Location;
		return FTransform(ActorLocation + Transform.Location, Transform.Scale);
	}
	FTransform GetTransform() const
	{
		return Transform;
	}
	FVector2D GetComponentLocation() const
	{
		return Transform.Location;
	}
	void SetComponentLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}
	void SetComponentScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}

};

