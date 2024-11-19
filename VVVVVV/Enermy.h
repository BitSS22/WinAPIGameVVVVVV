#pragma once
#include "PistonEntity.h"

// Ό³Έν :
class AEnermy : public APistonEntity
{
public:
	AEnermy();
	~AEnermy();

	AEnermy(const AEnermy& _Other) = delete;
	AEnermy(AEnermy&& _Other) noexcept = delete;
	AEnermy& operator=(const AEnermy& _Other) = delete;
	AEnermy& operator=(AEnermy&& _Other) noexcept = delete;

private:

public:

private:

};

