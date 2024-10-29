#pragma once

#include <EngineBase/EngineMath.h>

class ULevel;

class AActor
{
public:
	using Super = AActor;
	friend class ULevel;
public:
	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

private:
	ULevel* World = nullptr;
	FTransform Transfrom = {};

public:
	virtual void BeginPlay()
	{}
	virtual void Tick()
	{}
	virtual void Render() const;

private:

public:
	ULevel* GetWorld() const
	{
		return World;
	}
	FVector2D GetActorLocation() const
	{
		return Transfrom.Location;
	}
	void SetActorLocation(FVector2D _Location)
	{
		Transfrom.Location = _Location;
	}
	void AddActorLocation(FVector2D _Location)
	{
		Transfrom.Location += _Location;
	}
	void SetActorScale(FVector2D _Scale)
	{
		Transfrom.Scale = _Scale;
	}
};

