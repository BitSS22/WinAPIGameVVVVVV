#include "pch.h"
#include "Actor.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render() const
{
	FVector2D LeftTop = Transfrom.Location - Transfrom.Scale.Half();
	FVector2D RightBottom = Transfrom.Location + Transfrom.Scale.Half();

	HDC BackDC = UEngineAPICore::GetCore()->GetMainWindow().GetBackBufferImageDC();

	Rectangle(BackDC, LeftTop.iX(), LeftTop.iY(), RightBottom.iX(), RightBottom.iY());
}

