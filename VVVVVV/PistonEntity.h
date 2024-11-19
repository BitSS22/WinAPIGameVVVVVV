#pragma once
#include "Entity.h"

class APistonEntity : public AEntity
{
public:
	APistonEntity();
	~APistonEntity();

	APistonEntity(const APistonEntity& _Other) = delete;
	APistonEntity(APistonEntity&& _Other) noexcept = delete;
	APistonEntity& operator=(const APistonEntity& _Other) = delete;
	APistonEntity& operator=(APistonEntity&& _Other) noexcept = delete;

private:
	FVector2D DefualtLocation = {};
	FVector2D DefualtDir = FVector2D::ZERO;
	FVector2D Dir = FVector2D::ZERO;
	float Speed = EGameConst::DefualtSpeed;
	float MoveLenght = 0.f;
	float MoveLenghtOffset = 0.f;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void SetEntity(const RoomEntityData& _Data) override;
	RoomEntityData GetEntityData() override;
	
private:

public:
	virtual void AddEntityLocation(const FVector2D& _Location) override;
	void AddSpeed(float _Speed);
	void AddMoveLenght(float _Lenght);
	void AddMoveLenghtOffset(float _Offset);
	void AddDir(const FVector2D& _Dir);
	void SetDir(const FVector2D& _Dir);

	float GetSpeed()
	{
		return Speed;
	}
	float GetMoveLenght()
	{
		return MoveLenght;
	}
	float GetMoveLenghtOffset()
	{
		return MoveLenghtOffset;
	}
	virtual FVector2D GetEntityLocation() const override
	{
		return DefualtLocation;
	}
	FVector2D GetEntityDefualtDir()
	{
		return DefualtDir;
	}
	FVector2D GetEntityDir()
	{
		return Dir;
	}

};

