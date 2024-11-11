#pragma once
#include "Entity.h"

class AEnermy : public AEntity
{
public:
	AEnermy();
	~AEnermy();

	AEnermy(const AEnermy& _Other) = delete;
	AEnermy(AEnermy&& _Other) noexcept = delete;
	AEnermy& operator=(const AEnermy& _Other) = delete;
	AEnermy& operator=(AEnermy&& _Other) noexcept = delete;

private:
	float Speed = EGameConst::DefualtSpeed;
	FVector2D StartPos = {};
	FVector2D EndPos = {};

public:
	virtual void BeginPlay() override;
	
private:

};

