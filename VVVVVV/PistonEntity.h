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

	virtual void SetEntity(const AGameWorld::RoomData::RoomEntityData& _Data) override;
	AGameWorld::RoomData::RoomEntityData GetEntityData() override;
	
private:

public:
	void AddSpeed(float _Speed)
	{
		Speed += _Speed;
	}
	void AddMoveLenght(float _Lenght)
	{
		MoveLenght += _Lenght;
		SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
		Dir = DefualtDir;
	}
	void AddMoveLenghtOffset(float _Offset)
	{
		MoveLenghtOffset += _Offset;
		SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
		Dir = DefualtDir;
	}
	void AddDefualtLocation(FVector2D _Location)
	{
		SetActorLocation(DefualtLocation += _Location);
		DefualtLocation = GetActorLocation();
		SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
		Dir = DefualtDir;
	}

	void AddDir(FVector2D _Dir)
	{
		DefualtDir += _Dir;
		if (DefualtDir != FVector2D::ZERO)
			DefualtDir.Nomalize();
		Dir = DefualtDir;
		SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
	}
	void SetDir(FVector2D _Dir)
	{
		DefualtDir = _Dir;
		if (DefualtDir != FVector2D::ZERO)
			DefualtDir.Nomalize();
		Dir = DefualtDir;
		SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
	}

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
	FVector2D GetEntityDefualtLocation()
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

