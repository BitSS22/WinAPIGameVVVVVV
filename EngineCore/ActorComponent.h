#pragma once

// ���� :
class UActorComponent : public UObject
{
public:
	friend class AActor;
	typedef UActorComponent Super;
public:
	UActorComponent();
	virtual ~UActorComponent() = 0;

	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

private:
	AActor* ParentActor = nullptr;

public:
	virtual void BeginPlay()
	{}
	virtual void ComponentTick()
	{}

private:

public:
	AActor* GetActor() const
	{
		return ParentActor;
	}
	virtual bool IsActive() const override
	{
		return UObject::IsActive() == true && GetActor()->IsActive();
	}
	virtual bool IsDestroy() const override
	{
		return UObject::IsDestroy() || GetActor()->IsDestroy();
	}

};

