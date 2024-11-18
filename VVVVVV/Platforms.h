#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class APlatforms : public AActor
{
public:
	APlatforms();
	~APlatforms();

	APlatforms(const APlatforms& _Other) = delete;
	APlatforms(APlatforms&& _Other) noexcept = delete;
	APlatforms& operator=(const APlatforms& _Other) = delete;
	APlatforms& operator=(APlatforms&& _Other) noexcept = delete;

private:
	virtual void BeginPlay() override;
	virtual void Tick() override;

public:

private:

};

