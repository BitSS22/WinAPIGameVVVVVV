#pragma once

class USpriteRenderer;

class AFade : public AActor
{
public:
	AFade();
	~AFade();

	AFade(const AFade& _Other) = delete;
	AFade(AFade&& _Other) noexcept = delete;
	AFade& operator=(const AFade& _Other) = delete;
	AFade& operator=(AFade&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	std::function<void()> Effect = nullptr;
	float AccTime = 0.f;
	float FadeTime = 1.0f;
	bool FadeInEnd = false;
	bool FadeOutEnd = false;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	void PlayFadeIn();
	void PlayFadeOut();

private:
	void FadeIn();
	void FadeOut();

public:
	bool IsFadeInEnd() const
	{
		return FadeInEnd;
	}
	bool IsFadeOutEnd() const
	{
		return FadeOutEnd;
	}

};

