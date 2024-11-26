#pragma once
#include <EnginePlatform/EngineSound.h>

class ATitleLogo;
class USpriteRenderer;
class AFade;
// Ό³Έν :
class ATitleGameMode : public AGameMode
{
public:
	ATitleGameMode();
	~ATitleGameMode();

	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

private:
	AFade* Fade = nullptr;
	USpriteRenderer* BackGround = nullptr;
	USoundPlayer BGM = {};
	static const int LogoCount = 6;
	ATitleLogo* Logos[LogoCount] = {};
	USpriteRenderer* Menu = nullptr;
	float ColorAccTime = 0.f;
	float ColorChangeTime = 2.f;
	float BlankAccTime = 0.f;
	float BlankTime = 0.8f;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;

	virtual void LevelChangeStart() override;
	virtual void LevelChangeEnd() override;

	void ChangeColor(EGameColor _Color);

private:

};

