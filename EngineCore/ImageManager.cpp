#include "pch.h"
#include "ImageManager.h"
#include <EngineBase/EnginePath.h>
#include "EngineSprite.h"

UImageManager::UImageManager()
{
}

UImageManager::~UImageManager()
{
	for (auto& i : Images)
	{
		if (i.second != nullptr)
		{
			delete i.second;
			i.second = nullptr;
		}
	}

	for (auto& i : Sprites)
	{
		if (i.second != nullptr)
		{
			delete i.second;
			i.second = nullptr;
		}
	}
}

void UImageManager::Load(string_view _KeyName, string_view _Path)
{
	UEnginePath path = _Path;

	if (path.IsDirectory() == true)
		MSGASSERT(nullptr, _Path, "는 파일경로입니다.");
	if (path.IsExists() == false)
		MSGASSERT(nullptr, _Path, "는 유효하지 않은 파일경로입니다.");

	UEngineWindowImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	string UpperName = UEngineString::ToUpper(_KeyName);

	UEngineWindowImage* NewImage = new UEngineWindowImage();
	NewImage->Load(WindowImage, _Path);
	Images.insert(make_pair(UpperName, NewImage));

	UEngineSprite* NewSprite = new UEngineSprite();

	FTransform form = {};
	form.Location = FVector2D(0.f, 0.f);
	form.Scale = NewImage->GetImageScale();

	NewSprite->PushData(NewImage, form);
	Sprites.insert(make_pair(UpperName, NewSprite));
}

void UImageManager::Load(string_view _Path)
{
	UEnginePath path = _Path;

	Load(path.GetFileName(), _Path);
}

UEngineSprite* UImageManager::FindSprite(string_view _KeyName)
{
	if (IsLoadSprite(_KeyName) == false)
		MSGASSERT(nullptr, _KeyName, "는 Load 되지 않은 Sprite입니다.");

	return Sprites[UEngineString::ToUpper(_KeyName)];
}

void UImageManager::CutSprite(string_view _KeyName, FVector2D _CuttingSize)
{
	string UpperName = UEngineString::ToUpper(_KeyName);

	if (Sprites.contains(UpperName) == false)
		MSGASSERT(nullptr, _KeyName, "라는 이름의 Sprite는 존재하지 않습니다.");
	if (Images.contains(UpperName) == false)
		MSGASSERT(nullptr, _KeyName, "라는 이름의 Image는 존재하지 않습니다.");

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWindowImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();

	if (Image->GetImageScale().iX() % _CuttingSize.iX() != 0)
		MSGASSERT(nullptr, _KeyName, "의 사이즈가 정확하지 않습니다.");
	if (Image->GetImageScale().iY() % _CuttingSize.iY() != 0)
		MSGASSERT(nullptr, _KeyName, "의 사이즈가 정확하지 않습니다.");

	int SpriteX = Image->GetImageScale().iX() / _CuttingSize.iX();
	int SpriteY = Image->GetImageScale().iY() / _CuttingSize.iY();

	FTransform CuttingTrans = {};
	CuttingTrans.Location = FVector2D::ZERO;
	CuttingTrans.Scale = _CuttingSize;

	for (size_t y = 0; y < SpriteY; ++y)
	{
		for (size_t x = 0; x < SpriteX; ++x)
		{
			Sprite->PushData(Image, CuttingTrans);
			CuttingTrans.Location.X += _CuttingSize.X;
		}

		CuttingTrans.Location.X = 0.f;
		CuttingTrans.Location.Y += _CuttingSize.Y;
	}
}

void UImageManager::CreateCutSprite(string_view _SearchKeyName, string_view _NewSpriteKeyName, FVector2D _StartPos, FVector2D _CuttingSize, FVector2D _XYOffSet, UINT _Xcount, UINT _ImageCount)
{
	string SearchName = UEngineString::ToUpper(_SearchKeyName);
	string NewSpriteName = UEngineString::ToUpper(_NewSpriteKeyName);

	if (_Xcount <= 0)
		MSGASSERT(nullptr, "이미지의 가로 갯수가 0 이하입니다.");
	if (_ImageCount <= 0)
		MSGASSERT(nullptr, "총 이미지 갯수가 0 이하입니다.");
	if (Sprites.contains(SearchName) == false)
		MSGASSERT(nullptr, _SearchKeyName, "라는 이름의 Sprite는 로드할 수 없습니다.");
	if (Images.contains(SearchName) == false)
		MSGASSERT(nullptr, _SearchKeyName, "라는 이름의 Sprite는 로드할 수 없습니다.");
	if (Sprites.contains(NewSpriteName) == true)
		MSGASSERT(nullptr, _NewSpriteKeyName, "라는 이름의 Sprite가 이미 존재합니다.");
	if (Images.contains(NewSpriteName) == true)
		MSGASSERT(nullptr, _NewSpriteKeyName, "라는 이름의 Image가 이미 존재합니다.");


	UEngineSprite* Sprite = Sprites[SearchName];
	UEngineWindowImage* Image = Images[SearchName];

	Sprite->ClearSpriteData();

	UINT YCount = _ImageCount / _Xcount;
	if (_ImageCount % _Xcount > 0)
		++YCount;

	float TotalSizeX = _StartPos.X + (_CuttingSize.X * _Xcount) + (_XYOffSet.X * (_Xcount - 1));
	float TotalSizeY = _StartPos.Y + (_CuttingSize.Y * YCount) + (_XYOffSet.Y * (YCount - 1));

	if (TotalSizeX > Image->GetImageScale().X)
		MSGASSERT(nullptr, "필요한 이미지 가로 사이즈가 원본 이미지 사이즈보다 큽니다.");
	if (TotalSizeY > Image->GetImageScale().Y)
		MSGASSERT(nullptr, "필요한 이미지 세로 사이즈가 원본 이미지 사이즈보다 큽니다.");

	FVector2D TotalSize = FVector2D(static_cast<int>(TotalSizeX), static_cast<int>(TotalSizeY));


	UEngineWindowImage* NewImage = new UEngineWindowImage();
	UEngineSprite* NewSprite = new UEngineSprite();
	NewImage->Create(UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage(), TotalSize);

	BitBlt(NewImage->GetDC(), 0, 0, static_cast<int>(TotalSizeX), static_cast<int>(TotalSizeY), Image->GetDC(), static_cast<int>(_StartPos.X), static_cast<int>(_StartPos.Y), SRCCOPY);

	Images.insert(make_pair(NewSpriteName, NewImage));
	Sprites.insert(make_pair(NewSpriteName, NewSprite));

	FVector2D CuttingPos = {};

	for (UINT y = 0; y < YCount; ++y)
	{
		CuttingPos.Y = _CuttingSize.Y * y + _XYOffSet.Y * y;

		for (UINT x = 0; x < _Xcount; ++x)
		{
			CuttingPos.X = _CuttingSize.X * x + _XYOffSet.X * x;
			FTransform insertInst = {};
			insertInst.Scale = _CuttingSize;
			insertInst.Location = CuttingPos;
			NewSprite->PushData(NewImage, insertInst);
		}
		CuttingPos.X = 0.f;
	}
}

