#pragma once

class USpriteRenderer;
// Ό³Έν :
class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

private:
	float Speed = 800.f;
	USpriteRenderer* SpriteRenderer = nullptr;

public:
	void BeginPlay() override;
	void Tick() override;

private:

};

