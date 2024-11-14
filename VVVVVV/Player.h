#pragma once
#include "Entity.h"

class USpriteRenderer;

class APlayer : public AEntity
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
	bool Flip = false;
	bool OnGround = false;
	float GravitySpeed = 1000.f;

public:
	void BeginPlay() override;
	void Tick() override;

private:

};

