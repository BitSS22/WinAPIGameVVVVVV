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
	HBITMAP BitMap = nullptr;

public:
	void Create(HDC _hdc)
	{}
	void Create(FVector2D _Scale);

private:

public:
	HDC GetDC()
	{
		return ImageDC;
	}

};

