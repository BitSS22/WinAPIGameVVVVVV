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
}

void ABackGround::Tick()
{
	if (KEY_PRESS('P'))
	{
		for (size_t i = 0; i < 2500; ++i)
		{
			Sprite->SetSprite("BackGrounds::23 Ending", 0);
		}
	}

	if (KEY_DOWN('O'))
		Sprite->SetSprite("Debug BackGround.png", 0);
}

