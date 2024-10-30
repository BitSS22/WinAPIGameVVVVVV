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
		MSGASSERT(nullptr, _Path, "�� ���ϰ���Դϴ�.");
	if (path.IsExists() == false)
		MSGASSERT(nullptr, _Path, "�� ��ȿ���� ���� ���ϰ���Դϴ�.");

	UEngineWindowImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowMainImage();

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
		MSGASSERT(nullptr, _KeyName, "�� Load ���� ���� Sprite�Դϴ�.");

	return Sprites[UEngineString::ToUpper(_KeyName)];
}

void UImageManager::CutSprite(string_view _KeyName, FVector2D _CuttingSize)
{
	string UpperName = UEngineString::ToUpper(_KeyName);

	if (Sprites.contains(UpperName) == false)
		MSGASSERT(nullptr, UpperName, "��� �̸��� Sprite�� �������� �ʽ��ϴ�.");
	if (Images.contains(UpperName) == false)
		MSGASSERT(nullptr, UpperName, "��� �̸��� Image�� �������� �ʽ��ϴ�.");

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWindowImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();

	if (Image->GetImageScale().iX() % _CuttingSize.iX() != 0)
		MSGASSERT(nullptr, UpperName, "�� ����� ��Ȯ���� �ʽ��ϴ�.");
	if (Image->GetImageScale().iY() % _CuttingSize.iY() != 0)
		MSGASSERT(nullptr, UpperName, "�� ����� ��Ȯ���� �ʽ��ϴ�.");

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

void UImageManager::CutSprite(string_view _KeyName, FVector2D _StartPos, FVector2D _CuttingSize, FVector2D _XYOffSet, UINT _Xcount, UINT _ImageCount)
{
}

