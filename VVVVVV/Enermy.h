#pragma once
#include "Entity.h"

class AEnermy : public AEntity
{
public:
	AEnermy();
	AEnermy(int a) {}
	~AEnermy();

	AEnermy(const AEnermy& _Other) = delete;
	AEnermy(AEnermy&& _Other) noexcept = delete;
	AEnermy& operator=(const AEnermy& _Other) = delete;
	AEnermy& operator=(AEnermy&& _Other) noexcept = delete;

private:
	float Speed = EGameConst::DefualtSpeed;
	FVector2D Dir = FVector2D::RIGHT;
	FVector2D DefualtLocation = {};
	float MoveLenght = 100.f;
	float MoveLenghtOffset = 0.f;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	void EnermyDefaultSetUp(std::string_view _Name, FVector2D _Location, FVector2D _Dir, float _Speed, float _MoveLength, float _MoveOffset);
	
private:

public:
	void AddSpeed(float _Speed)
	{
		Speed += _Speed;
	}
	void SetDir(FVector2D _Dir)
	{
		Dir = _Dir;
		SetActorLocation(DefualtLocation + (Dir * MoveLenghtOffset));
	}
	void AddMoveLenght(float _Lenght)
	{
		MoveLenght += _Lenght;
		SetActorLocation(DefualtLocation + (Dir * MoveLenghtOffset));
	}
	void AddMoveLenghtOffset(float _Offset)
	{
		MoveLenghtOffset += _Offset;
		SetActorLocation(DefualtLocation + (Dir * MoveLenghtOffset));
	}
	virtual void AddEntityLocation(FVector2D _Location) override
	{
		SetActorLocation(DefualtLocation += _Location);
		DefualtLocation = GetActorLocation();
		SetActorLocation(DefualtLocation + (Dir * MoveLenghtOffset));
	}

	float GetSpeed()
	{
		return Speed;
	}
	FVector2D GetDir()
	{
		return Dir;
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
};

