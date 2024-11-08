#include "pch.h"
#include "BackGround.h"

ABackGround::ABackGround()
{
}

ABackGround::~ABackGround()
{
}

void ABackGround::BeginPlay()
{
	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Debug BackGround.png", 0);
	Sprite->SetSpriteScale(1.f, Sprite->GetCurIndex());
	Sprite->SetOrder(ERenderOrder::BACK_GROUND);
	Sprite->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	for (size_t i = 0; i < 6; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Stars", 0);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACK_GROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		Effects.push_back(Star(StarSprite, -100.f));
	}
	for (size_t i = 0; i < 10; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Stars", 1);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACK_GROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		Effects.push_back(Star(StarSprite, -150.f));
	}
	for (size_t i = 0; i < 20; ++i)
	{
		USpriteRenderer* StarSprite = CreateDefaultSubObject<USpriteRenderer>();
		StarSprite->SetSprite("Stars", 2);
		StarSprite->SetSpriteScale(1.f, StarSprite->GetCurIndex());
		StarSprite->SetOrder(ERenderOrder::BACK_GROUND_EFFECT);
		StarSprite->SetComponentLocation(FVector2D(UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.X), UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y)));
		Effects.push_back(Star(StarSprite, -200.f));
	}
}

void ABackGround::Tick()
{
	if (EffectValue == true)
	{
		FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

		for (size_t i = 0; i < Effects.size(); ++i)
		{
			Effects[i].Sprite->AddComponentLocation(FVector2D(Effects[i].Speed * GET_DELTA, 0.f));
			FVector2D Pos = Effects[i].Sprite->GetComponentLocation();

			if (Pos.X < 0)
			{
				Pos.X += WindowSize.X;
				Pos.Y = UEngineAPICore::GetCore()->GetRandomDevice().GetRandomFloat(0.f, WindowSize.Y);
				Effects[i].Sprite->SetComponentLocation(Pos);
			}
		}
	}

	if (KEY_PRESS('P'))
	{
		Sprite->SetSprite("BackGrounds::23 Ending", 0);
		SetEffect(false);
	}

	if (KEY_DOWN('O'))
	{
		Sprite->SetSprite("Debug BackGround.png", 0);
		SetEffect(true);
	}
}

