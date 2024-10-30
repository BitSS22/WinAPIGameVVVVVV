#pragma once

// ���� :
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
	float Speed = 300.f;
	FVector2D Dir = FVector2D(0.f, 0.f);
	float AccTime = 0.f;

public:
	void BeginPlay() override;
	void Tick() override;

private:

};

