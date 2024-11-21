#pragma once
#include "SceneComponent.h"
#include <EngineBase/EngineDelegate.h>
#include "EngineSprite.h"
#include <EngineCore/SceneComponent.h>
#include <map>

enum class PivotType
{
	Center,
	Left,
	LeftTop,
	Top,
	Botttom
};

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
	FVector2D Pivot = FVector2D(0.5f, 0.5f);
	bool IsCameraEffect = true;
	float CameraEffectScale = 1.f;
	std::map<std::string, FrameAnimation> FrameAnimations = {};
	FrameAnimation* CurAnimation = nullptr;
	unsigned char Alpha = 255;
	float CurAnimationSpeed = 1.f;

public:
	virtual void BeginPlay() override;
	virtual void ComponentTick() override;
	void Render();
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float _Time, bool _Loop);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);
	void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);

private:

public:
	int GetOrder() const
	{
		return Order;
	}
	void SetOrder(int _Order);
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	int GetCurIndex() const
	{
		return CurIndex;
	}
	int GetMaxIndex() const
	{
		return Sprite->GetSpriteCount();
	}
	std::string GetCurSpriteName() const
	{
		return Sprite->GetName();
	}
	void SetCameraEffect(bool _Value)
	{
		IsCameraEffect = _Value;
	}
	void SetCameraEffectScale(float _Effect);
	void SetSprite(std::string_view _Name, int _CurIndex);
	void SetSpriteScale(float _Ratio, int _CurIndex);
	void SetPivotValue(FVector2D _Pivot);
	void SetPivotType(PivotType _Type);
	void SetAlphaChar(unsigned char _Value)
	{
		Alpha = _Value;
	}
	void SetAlphaFloat(float _Value)
	{
		Alpha = static_cast<unsigned char>(UEngineMath::Clamp(_Value, 0.f, 1.f));
	}
	void OffAnimation()
	{
		CurAnimation = nullptr;
	}
	bool IsCurAnimationEnd()
	{
		return CurAnimation->IsEnd;
	}
	void SetAnimationSpeed(float _Speed)
	{
		CurAnimationSpeed = _Speed;
	}
	void ResetAnimationSpeed()
	{
		CurAnimationSpeed = 1.f;
	}

public:
	INNER_CLASS struct FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex = {};
		std::vector<float> FrameTime = {};
		int CurIndex = 0;
		float CurTime = 0.f;
		bool Loop = true;
		bool IsEnd = false;
		std::map<int, UEngineDelegate> Events = {};

	public:
		void Reset()
		{
			CurIndex = 0;
			CurTime = 0.f;
			IsEnd = false;
		}

	};

};

