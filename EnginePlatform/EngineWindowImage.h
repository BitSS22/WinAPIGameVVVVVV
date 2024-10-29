#pragma once
#include <Windows.h>

// Ό³Έν :
class UEngineWindowImage
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

private:

public:
	HDC GetDC()
	{
		return ImageDC;
	}

};

