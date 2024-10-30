#pragma once
#include <Windows.h>

// Ό³Έν :
class UEngineWindowImage : public UObject
{
public:
	UEngineWindowImage();
	~UEngineWindowImage();

	UEngineWindowImage(const UEngineWindowImage& _Other) = delete;
	UEngineWindowImage(UEngineWindowImage&& _Other) noexcept = delete;
	UEngineWindowImage& operator=(const UEngineWindowImage& _Other) = delete;
	UEngineWindowImage& operator=(UEngineWindowImage&& _Other) noexcept = delete;

private:
	HDC ImageDC = nullptr;
	HBITMAP hBitMap = nullptr;
	BITMAP Info = {};

public:
	void Create(HDC _hDC)
	{
		ImageDC = _hDC;
	}
	void Create(UEngineWindowImage* _TargetImage, FVector2D _Scale);
	void CopyBit(UEngineWindowImage* _Destination, const FTransform& _transform);
	void CopyToBit(UEngineWindowImage* _TargetImage, const FTransform& _transform);
	void CopyTrans(UEngineWindowImage* _TargetImage, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color = UColor(0, 0, 0, 0));
	void CopyToTrans(UEngineWindowImage* _TargetImage, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color = UColor(0, 0, 0, 0));
	void Load(UEngineWindowImage* _TargetImage, string_view _Path);

private:

public:
	HDC GetDC() const
	{
		return ImageDC;
	}
	FVector2D GetImageScale() const
	{
		return FVector2D(Info.bmWidth, Info.bmHeight);
	}

};

