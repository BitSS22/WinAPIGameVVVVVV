#include "pch.h"
#include "EngineWindow.h"
#include "EngineWindowImage.h"

UEngineWindowImage::UEngineWindowImage()
{
}

UEngineWindowImage::~UEngineWindowImage()
{
}

void UEngineWindowImage::Create(UEngineWindowImage* _TargetImage, FVector2D _Scale)
{
	if (_TargetImage == nullptr)
		MSGASSERT(nullptr, "Main WindowDC가 nullptr입니다.");

	HDC NewDC = CreateCompatibleDC(_TargetImage->GetDC());
	HBITMAP NewBitmap = CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY());

	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewDC, NewBitmap));
	DeleteObject(OldBitmap);

	hBitMap = NewBitmap;
	ImageDC = NewDC;

	GetObject(hBitMap, sizeof(HBITMAP), &Info);
}

void UEngineWindowImage::CopyBit(UEngineWindowImage* _origin, const FTransform& _transform)
{
	if (_origin == nullptr)
		MSGASSERT(nullptr, "원본 이미지가 nullptr입니다.");
	else
	{
		FVector2D LT = _transform.CenterLeftTop();
		BitBlt(ImageDC, LT.iX(), LT.iY(), _transform.Scale.iX(), _transform.Scale.iY(), _origin->ImageDC, 0, 0, SRCCOPY);
	}
}

void UEngineWindowImage::CopyToBit(UEngineWindowImage* _TargetImage, const FTransform& _transform)
{
	if (_TargetImage == nullptr)
		MSGASSERT(nullptr, "TargetImage가 nullptr입니다.");
	else
		_TargetImage->CopyBit(this, _transform);
}

