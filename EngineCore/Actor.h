#pragma once

#include <EngineBase/EngineMath.h>
#include <EngineCore/ImageManager.h>

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
	ULevel* World = nullptr;
	FTransform Transform = {};
	static std::list<UActorComponent*> ComponentBeginList;
	std::list<UActorComponent*> Components = {};

public:
	virtual void BeginPlay()
	{}
	virtual void Tick()
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

public:
	ULevel* GetWorld() const
	{
		return World;
	}
	FVector2D GetActorLocation() const
	{
		return Transform.Location;
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
	FTransform GetTransform() const
	{
		return Transform;
	}
};

