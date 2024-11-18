#pragma once
#include <EngineCore/Actor.h>
#include "MoveEntity.h"


// Ό³Έν :
class APlatform : public AMoveEntity
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

private:

};

