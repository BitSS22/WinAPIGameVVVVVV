#pragma once
#include "Entity.h"

class AMoveEntity : public AEntity
{
public:
	AMoveEntity();
	~AMoveEntity();

	AMoveEntity(const AMoveEntity& _Other) = delete;
	AMoveEntity(AMoveEntity&& _Other) noexcept = delete;
	AMoveEntity& operator=(const AMoveEntity& _Other) = delete;
	AMoveEntity& operator=(AMoveEntity&& _Other) noexcept = delete;

private:
	float Speed = EGameConst::DefualtSpeed;
	FVector2D Dir = FVector2D::ZERO;
	FVector2D DefualtDir = FVector2D::ZERO;
	FVector2D DefualtLocation = {};
	float MoveLenght = 0.f;
	float MoveLenghtOffset = 0.f;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	void MoveEntityDefaultSetUp(std::string_view _Name, FVector2D _Location, FVector2D _Dir, float _Speed, float _MoveLength, float _MoveOffset);
	
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
	virtual void AddEntityLocation(FVector2D _Location) override
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

