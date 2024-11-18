#pragma once
#include <EngineCore/Actor.h>
#include "PistonEntity.h"


// Ό³Έν :
class APlatform : public APistonEntity
{
public:
	APlatform();
	~APlatform();

	APlatform(const APlatform& _Other) = delete;
	APlatform(APlatform&& _Other) noexcept = delete;
	APlatform& operator=(const APlatform& _Other) = delete;
	APlatform& operator=(APlatform&& _Other) noexcept = delete;

private:
	virtual void BeginPlay() override;
	virtual void Tick() override;

public:
	virtual APlatform* GetThis() override
	{
		return this;
	}

private:

};

