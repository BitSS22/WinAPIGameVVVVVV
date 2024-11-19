#pragma once
#include "GameWorld.h"

enum class EEffectType
{
	Star,
	Rect,
	None
};

class ABackGround : public AActor
{
private:
	struct StarEffect
	{
	public:
		USpriteRenderer* Sprite = nullptr;
		float Speed = 0.f;
		FVector2D Dir = {};
	};
	struct RectEffect
	{
	public:
		USpriteRenderer* Sprite = nullptr;
		float Speed = 0.f;
		FVector2D Dir = {};
	};
public:
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	EBackGroundType BackGroundType = EBackGroundType::Space;
	float AnimationSpeed = 320.f;
	std::vector<StarEffect> StarEffects = {};
	std::vector<RectEffect> RectEffects = {};

	std::function<void()> CurAnimation = nullptr;
	std::function<void()> CurEffect = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	void SetBackGround(const RoomBackGroundData& _Data);
	RoomBackGroundData GetBackGroundData();

private:
	void PlayHorizontalAnimation();
	void PlayVerticalAnimation();
	void PlayTowerAnimation();

	void PlayStarEffect();
	void PlayRectEffect();

	void SetEffect(EEffectType _Type);

	void FileLoadInit();

public:

};

