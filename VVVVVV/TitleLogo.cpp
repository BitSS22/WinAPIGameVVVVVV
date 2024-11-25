#include "pch.h"
#include "TitleLogo.h"

ATitleLogo::ATitleLogo()
{
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::SetLogoColor(EGameColor _Color)
{
	Sprite->SetSprite(Sprite->GetCurSpriteName(), static_cast<int>(_Color));
}

void ATitleLogo::LogoInit()
{
	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Logos:: V", 0);
	Sprite->SetSpriteScale(1.f, 0);
	Sprite->SetOrder(ERenderOrder::BACKGROUND_EFFECT);
}
