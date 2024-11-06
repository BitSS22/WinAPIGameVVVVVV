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
		MSGASSERT(nullptr, "�̹����� ũ�Ⱑ 0�Դϴ�.");

	Data.push_back({ _Image, _Trans });
	++SpriteCount;
}

