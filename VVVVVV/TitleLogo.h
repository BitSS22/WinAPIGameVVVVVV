#pragma once

// Ό³Έν :
class ATitleLogo : public AActor
{
public:
	ATitleLogo();
	~ATitleLogo();

	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;

public:
	void SetLogoColor(EGameColor _Color);
	void LogoInit();

private:

};

