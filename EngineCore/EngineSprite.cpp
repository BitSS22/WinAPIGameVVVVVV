#include "pch.h"
#include "EngineSprite.h"

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

void UEngineSprite::PushData(UEngineWindowImage* _Image, const FTransform& _Trans)
{
	if (_Trans.Scale.IsZeroOr() == true)
		MSGASSERT(nullptr, "이미지의 크기가 0입니다.");

	Data.push_back({ _Image, _Trans });
	++SpriteCount;
}

