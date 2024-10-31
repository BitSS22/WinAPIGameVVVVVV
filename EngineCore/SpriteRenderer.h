#pragma once
#include "SceneComponent.h"

// Ό³Έν :
class USpriteRenderer : public USceneComponent
{
public:
	INNER_CLASS struct FrameAnimation;
public:
	USpriteRenderer();
	~USpriteRenderer();

	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

private:
	UEngineSprite* Sprite = nullptr;
	int CurIndex = 0;
	int Order = 0;

public:
	virtual void BeginPlay() override;
	virtual void ComponentTick() override;
	void Render();
	void SetSprite(std::string_view _Name, int _CurIndex = 0);
	void SetSpriteScale(float _Ratio = 1.f, int _CurIndex = 0);
	void CreateAnimation(std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame)
	{}

private:

public:
	int GetOrder()
	{
		return Order;
	}
	void SetOrder(int _Order);
	
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

public:
	INNER_CLASS struct FrameAnimation
	{
	private:
		std::vector<int> FrameIndex = {};
		std::vector<float> FrameTime = {};
		float Inter = 0.f;
	};

};

