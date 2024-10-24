#pragma once

// Ό³Έν :
class AActor
{
public:
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
	FVector2D Location = FVector2D::ZERO;
	FVector2D Scale = FVector2D::ZERO;

public:
	virtual void BeginPlay()
	{}
	virtual void Tick()
	{}
	virtual void Render();

private:

public:
	ULevel* GetWorld()
	{
		return World;
	}
	void SetActorLocation(FVector2D _Location)
	{
		Location = _Location;
	}
	void AddActorLocation(FVector2D _Location)
	{
		Location += _Location;
	}
	void SetActorScale(FVector2D _Scale)
	{
		Scale = _Scale;
	}
};

