#pragma once

enum class EBackGroundType
{
	Space,
	Horizontal,
	Vertical,
	Tower,
	Ending,
	Last
};

enum class EEffectType
{
	Star,
	Rect,
	Last
};

class ARoom;
// Ό³Έν :
class ABackGround : public AActor
{
public:
	friend class ATileMapEditorMode;
	friend class ARoom;
	friend class AGameWorld;
private:
	INNER_CLASS struct Effect;
public:
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	EBackGroundType CurBackGroundType = EBackGroundType::Last;
	std::vector<Effect> Effects = {};
	float AnimationSpeed = 320.f;
	bool EffectValue = false;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:
	void SetEffect(bool _Value)
	{
		for (size_t i = 0; i < Effects.size(); ++i)
			Effects[i].Sprite->SetActive(_Value);
		EffectValue = _Value;
	}

public:
	void SetBackGround(std::string_view _Name);

private:
	INNER_CLASS struct Effect
	{
	public:
		USpriteRenderer* Sprite = nullptr;
		EEffectType EffectType = EEffectType::Last;
		float Speed = 0.f;
		FVector2D Dir = {};
	};
};

