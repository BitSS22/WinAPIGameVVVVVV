#pragma once

#include <EngineBase/EngineMath.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/Level.h>
#include <EngineBase/TimeEvent.h>

class ULevel;
class UEngineSprite;
class UActorComponent;

class AActor : public UObject
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
	ULevel* GameWorld = nullptr;
	FTransform Transform = {};
	static std::list<UActorComponent*> ComponentBeginList;
	std::list<UActorComponent*> Components = {};

protected:
	UTimeEvent TimeEventer = {};

public:
	virtual void BeginPlay()
	{}
	virtual void Tick();
	virtual void LevelChangeStart()
	{}
	virtual void LevelChangeEnd()
	{}

	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject()
	{
		ComponentType* NewComponent = new ComponentType();

		UActorComponent* ComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);

		ComponentPtr->ParentActor = this;

		Components.push_back(NewComponent);
		ComponentBeginList.push_back(NewComponent);
		return NewComponent;
	}

private:
	static void ComponentBeginPlay();
	virtual void ReleaseCheck() override;
	virtual void ReleaseTimeCheck() override;

public:
	ULevel* GetWorld() const
	{
		return GameWorld;
	}
	FVector2D GetActorLocation() const
	{
		return Transform.Location;
	}
	FVector2D GetActorScale() const
	{
		return Transform.Scale;
	}
	void SetActorLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}
	void AddActorLocation(FVector2D _Location)
	{
		Transform.Location += _Location;
	}
	void SetActorScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}
	FTransform GetActorTransform() const
	{
		return Transform;
	}
	void SetActorTransform(const FTransform& _Transform)
	{
		Transform = _Transform;
	}
};

