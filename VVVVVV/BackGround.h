#pragma once

// Ό³Έν :
class ABackGround : public AActor
{
public:
	ABackGround();
	~ABackGround();

	ABackGround(const ABackGround& _Other) = delete;
	ABackGround(ABackGround&& _Other) noexcept = delete;
	ABackGround& operator=(const ABackGround& _Other) = delete;
	ABackGround& operator=(ABackGround&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	std::vector<USpriteRenderer*> Effects = {};

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

private:

public:
	void SetBackGround(std::string_view _Name, int _Index)
	{
		Sprite->SetSprite(_Name, _Index);
	}

};

