#include "pch.h"
#include "EngineWindowImage.h"

UEngineWindowImage::UEngineWindowImage()
{
}

UEngineWindowImage::~UEngineWindowImage()
{
}

void UEngineWindowImage::Create(FVector2D _Scale)
{
	HBITMAP NewBitmap = CreateCompatibleBitmap(nullptr, _Scale.iX(), _Scale.iY());
	HDC NewDC = CreateCompatibleDC(nullptr);

	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewDC, NewBitmap));
	DeleteObject(OldBitmap);
}

