#include "pch.h"
#include "Fade.h"

AFade::AFade()
{
}

AFade::~AFade()
{
}

void AFade::BeginPlay()
{
	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Fade::", 0);
	Sprite->SetOrder(ERenderOrder::Fade);
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	UEngineSprite* SpriteImage = UImageManager::GetInst().FindSprite("Fade::");
	Sprite->SetComponentScale(SpriteImage->GetSpriteData(0).Transform.Scale);
	Sprite->SetComponentLocation(WindowSize.Half());
	SetActive(true);
}

void AFade::Tick()
{
	if (Effect == nullptr)
		return;

	Effect();
}

void AFade::PlayFadeIn()
{
	SetActive(true);
	AccTime = 0.f;
	FadeInEnd = false;
	FadeOutEnd = false;
	Effect = bind(&AFade::FadeIn, this);
}

void AFade::PlayFadeOut()
{
	SetActive(true);
	AccTime = 0.f;
	FadeInEnd = false;
	FadeOutEnd = false;
	Effect = bind(&AFade::FadeOut, this);
}

void AFade::FadeIn()
{
	AccTime += GET_DELTA;
	FVector2D Location = {};
	Location.X = AccTime / FadeTime * 1280.f;
	SetActorLocation(Location);

	if (AccTime >= FadeTime)
	{
		AccTime = 0.f;
		SetActive(false);
		FadeInEnd = true;
		FadeOutEnd = false;
		Effect = nullptr;
	}
}

void AFade::FadeOut()
{
	AccTime += GET_DELTA;
	FVector2D Location = {};
	Location.X = -1280.f + AccTime / FadeTime * 1280.f;
	SetActorLocation(Location);

	if (AccTime >= FadeTime)
	{
		AccTime = 0.f;
		SetActorLocation(FVector2D(0.f, 0.f));
		SetActive(true);
		FadeInEnd = false;
		FadeOutEnd = true;
		Effect = nullptr;
	}
}

