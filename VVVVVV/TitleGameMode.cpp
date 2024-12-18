#include "pch.h"
#include "TitleGameMode.h"
#include "BackGround.h"
#include "TitleLogo.h"
#include "Fade.h"
#include <EnginePlatform/EngineSound.h>

bool ATitleGameMode::ClearMusic = false;
float ATitleGameMode::PrevClearTime = 0.f;

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());

	UEngineSprite* LogoSprite = UImageManager::GetInst().FindSprite("Logos:: V");
	FTransform LogoTransform = LogoSprite->GetSpriteData(0).Transform;

	BackGround = CreateDefaultSubObject<USpriteRenderer>();
	BackGround->SetOrder(ERenderOrder::BACKGROUND);
	BackGround->SetSprite("BackGrounds::03 Tower", 0);
	BackGround->SetSpriteScale(1.f, 0);

	for (int i = 0; i < LogoCount; ++i)
	{
		Logos[i] = GetWorld()->SpawnActor<ATitleLogo>();
		Logos[i]->LogoInit();
		FVector2D LogoLocation = GetActorLocation();
		LogoLocation.Y -= 56.f;
		LogoLocation.X = LogoLocation.X - (LogoTransform.Scale.X * LogoCount) / 2.f + LogoTransform.Scale.X * i + LogoTransform.Scale.HalfX();
		Logos[i]->SetActorLocation(LogoLocation);
	}

	Menu = CreateDefaultSubObject<USpriteRenderer>();
	Menu->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
	Menu->SetSprite("PressEnter::", 0);
	Menu->SetSpriteScale(1.f, 0);
	Menu->AddComponentLocation(FVector2D::DOWN * 40.f);

	Fade = GetWorld()->SpawnActor<AFade>();

}

void ATitleGameMode::Tick()
{
	Super::Tick();

	BackGround->AddComponentLocation(FVector2D::UP * 64.f * GET_DELTA);
	if (BackGround->GetComponentLocation().Y < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y - 1200.f)
		BackGround->AddComponentLocation(FVector2D(0.f, 1920.f));

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	ColorAccTime += GET_DELTA;
	if (ColorAccTime >= ColorChangeTime)
	{
		ColorAccTime -= ColorChangeTime;
		EGameColor Color = static_cast<EGameColor>(BackGround->GetCurIndex());
		ChangeColor(++Color);
	}

	BlankAccTime += GET_DELTA;
	if (BlankAccTime >= BlankTime)
	{
		BlankAccTime -= BlankTime;
		Menu->SetActiveSwitch();
	}

	if (KEY_DOWN(VK_RETURN))
		Fade->PlayFadeOut();

	if (Fade->IsFadeOutEnd() == true)
	{
		UEngineAPICore::GetCore()->OpenLevel("Play");
	}
}

void ATitleGameMode::LevelChangeStart()
{
	Fade->PlayFadeIn();

	if (ClearMusic == false)
	{
		BGM = UEngineSound::Play("02 Presenting VVVVVV.mp3");
		BGM.Loop();
	}
	else
	{
		BGM = UEngineSound::Play("14 Popular Potpourri.mp3");
		BGM.Loop();
		UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV // Clear Time : " + std::to_string(PrevClearTime));
	}
}

void ATitleGameMode::LevelChangeEnd()
{
	BGM.Stop();
}

void ATitleGameMode::ChangeColor(EGameColor _Color)
{
	for (int i = 0; i < LogoCount; ++i)
	{
		Logos[i]->SetLogoColor(_Color);
	}

	BackGround->SetSprite(BackGround->GetCurSpriteName(), static_cast<int>(_Color));
	Menu->SetSprite(Menu->GetCurSpriteName(), static_cast<int>(_Color));
}


