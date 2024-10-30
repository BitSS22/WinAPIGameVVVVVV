#pragma once
#include "Actor.h"

// Ό³Έν :
class AGameMode : public AActor
{
public:
	AGameMode();
	~AGameMode();

	AGameMode(const AGameMode& _Other) = delete;
	AGameMode(AGameMode&& _Other) noexcept = delete;
	AGameMode& operator=(const AGameMode& _Other) = delete;
	AGameMode& operator=(AGameMode&& _Other) noexcept = delete;

private:

public:
	virtual void Render() const override
	{}

private:

};

