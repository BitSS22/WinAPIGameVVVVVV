#include "pch.h"
#include "Actor.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render()
{
	FVector2D LeftTop = Location - Scale.Half();
	FVector2D RightBottom = Location + Scale.Half();

	HDC WindowDC = UEngineAPICore::GetCore()->GetMainWindow().GetBackBuffer();

	Rectangle(WindowDC, LeftTop.iX(), LeftTop.iY(), RightBottom.iX(), RightBottom.iY());
}

