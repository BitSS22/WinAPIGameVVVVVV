#pragma once
#include <EngineCore/GameMode.h>

class AGameWorld;
// Ό³Έν :
class APlayGameMode : public AGameMode
{
public:
	APlayGameMode();
	~APlayGameMode();

	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

private:
	AGameWorld* GameWorld = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override {};

private:

public:
	AGameWorld* GetGameWorld()
	{
		return GameWorld;
	}

};

