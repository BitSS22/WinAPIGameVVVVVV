#pragma once

enum class EBackGroundType
{
	SPACE,
	HORIZONTAL,
	VERTICAL,
	TOWER,
	ENDING,
	DEBUG
};

// Ό³Έν :
class ABackGround : public AActor
{
public:
	friend class ATileMapEditorMode;
private:
	INNER_CLASS struct Star;
public:
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	EBackGroundType CurBackGroundType = EBackGroundType::DEBUG;
	std::vector<Star> Effects = {};
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
	INNER_CLASS struct Star
	{
	public:
		USpriteRenderer* Sprite = nullptr;
		float Speed = 0.f;
	};
};

