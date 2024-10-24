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

public:
	virtual void BeginPlay()
	{}
	virtual void Tick()
	{}
	virtual void Render()
	{}

private:

public:
	ULevel* GetWorld()
	{
		return World;
	}

};

