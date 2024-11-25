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
	FVector2D MoveValue = FVector2D::ZERO;

	static bool FlipLineCollisionStay;
	static bool IsCollisionFlipLine;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void Collision(APlayer* _Player) override;
	void CollisionEnermy(APlayer* _Player);
	void CollisionPlatform(APlayer* _Player);
	void CollisionFlipLine(APlayer* _Player);

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

	float GetSpeed() const
	{
		return Speed;
	}
	float GetMoveLenght() const
	{
		return MoveLenght;
	}
	float GetMoveLenghtOffset() const
	{
		return MoveLenghtOffset;
	}
	virtual FVector2D GetEntityLocation() const override
	{
		return DefualtLocation;
	}
	FVector2D GetEntityDefualtDir() const
	{
		return DefualtDir;
	}
	FVector2D GetEntityDir() const
	{
		return Dir;
	}
	FVector2D GetMoveValue() const
	{
		return MoveValue;
	}
	static bool GetFlipLineCollisionStay()
	{
		return FlipLineCollisionStay;
	}
	static void SetFlipLineCollisionStay(bool _Value)
	{
		FlipLineCollisionStay = _Value;
	}
	static void SetIsCollisionFlipLine(bool _Value)
	{
		IsCollisionFlipLine = _Value;
	}

};

