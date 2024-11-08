#pragma once

// Ό³Έν :
class ABackGround : public AActor
{
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
	std::vector<Star> Effects = {};
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
	void SetBackGround(std::string_view _Name)
	{
		Sprite->SetSprite(_Name, 0);
	}

private:
	INNER_CLASS struct Star
	{
	public:
		USpriteRenderer* Sprite = nullptr;
		float Speed = 0.f;
	};
};

