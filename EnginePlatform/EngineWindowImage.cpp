#include "pch.h"
#include "EngineWindow.h"
#include "EngineWindowImage.h"
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>
#include <objidl.h>
#include <gdiplus.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

UEngineWindowImage::UEngineWindowImage()
{
}

UEngineWindowImage::~UEngineWindowImage()
{
	if (hBitMap != nullptr)
	{
		DeleteObject(hBitMap);
		hBitMap = nullptr;
	}
	if (ImageDC != nullptr)
	{
		DeleteDC(ImageDC);
		ImageDC = nullptr;
	}
}

void UEngineWindowImage::Create(UEngineWindowImage* _TargetImage, FVector2D _Scale)
{
	if (_TargetImage == nullptr)
		MSGASSERT(nullptr, "MainWindowDC가 nullptr입니다.");
	else
	{
		HBITMAP NewBitmap = CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY());
		HDC NewDC = CreateCompatibleDC(_TargetImage->GetDC());

		HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewDC, NewBitmap));
		DeleteObject(OldBitmap);

		hBitMap = NewBitmap;
		ImageDC = NewDC;

		GetObject(hBitMap, sizeof(BITMAP), &Info);
	}
}

void UEngineWindowImage::CopyBit(UEngineWindowImage* _origin, const FTransform& _transform)
{
	if (_origin == nullptr)
		MSGASSERT(nullptr, "원본 이미지가 nullptr입니다.");
	else
	{
		FVector2D LeftTop = _transform.CenterLeftTop();
		BitBlt(ImageDC, LeftTop.iX(), LeftTop.iY(), _transform.Scale.iX(), _transform.Scale.iY(), _origin->ImageDC, 0, 0, SRCCOPY);
	}
}

void UEngineWindowImage::CopyToBit(UEngineWindowImage* _TargetImage, const FTransform& _transform)
{
	if (_TargetImage == nullptr)
		MSGASSERT(nullptr, "TargetImage가 nullptr입니다.");
	else
		_TargetImage->CopyBit(this, _transform);
}

void UEngineWindowImage::CopyTrans(UEngineWindowImage* _origin, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color)
{
	if (_origin == nullptr)
		MSGASSERT(nullptr, "원본 이미지가 nullptr입니다.");
	else
		_origin->CopyToTrans(this, _RenderTrans, _LTImageTrans, _Color);

}

void UEngineWindowImage::CopyToTrans(UEngineWindowImage* _TargetImage, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color)
{
	if (_TargetImage == nullptr)
		MSGASSERT(nullptr, "TargetImage가 nullptr입니다.");
	else
	{
		HDC CopyDC = ImageDC;
		HDC TargetDC = _TargetImage->ImageDC;

		FVector2D LeftTop = _RenderTrans.CenterLeftTop();

		TransparentBlt(TargetDC, LeftTop.iX(), LeftTop.iY(), _RenderTrans.Scale.iX(), _RenderTrans.Scale.iY(), CopyDC
			, _LTImageTrans.Location.iX(), _LTImageTrans.Location.iY(), _LTImageTrans.Scale.iX(), _LTImageTrans.Scale.iY(), _Color.Color);
	}
}

void UEngineWindowImage::Load(UEngineWindowImage* _TargetImage, string_view _Path)
{
	UEnginePath path = _Path;

	string UpperExtTxt = UEngineString::ToUpper(path.GetExtension());

	HBITMAP NewBitmap = nullptr;

	if (".PNG" == UpperExtTxt)
	{
		ULONG_PTR GIDplusotoken = {};

		Gdiplus::GdiplusStartupInput Input = {};
		Gdiplus::GdiplusStartup(&GIDplusotoken, &Input, nullptr);

		std::wstring WidePath = UEngineString::AnsiToUnicode(_Path);

		Gdiplus::Image* ImagePtr = Gdiplus::Image::FromFile(WidePath.c_str());

		Gdiplus::Bitmap* BitmapPtr = reinterpret_cast<Gdiplus::Bitmap*>(ImagePtr->Clone());

		Gdiplus::Status Stat = BitmapPtr->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &NewBitmap);

		if (Stat != Gdiplus::Status::Ok)
			MSGASSERT(nullptr, _Path, " .png 로드에 실패 함.");

		delete BitmapPtr;
		delete ImagePtr;
	}
	else if (".BMP" == UpperExtTxt)
	{
		// TODO. BMP load code
	}

	if (NewBitmap == nullptr)
		MSGASSERT(nullptr, "Bitmap 생성 실패.");

	HDC NewDC = CreateCompatibleDC(_TargetImage->GetDC());

	HBITMAP OldBitmap = static_cast<HBITMAP>(SelectObject(NewDC, NewBitmap));
	DeleteObject(OldBitmap);

	hBitMap = NewBitmap;
	ImageDC = NewDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

