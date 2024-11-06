#include "pch.h"
#include "ImageManager.h"
#include <EngineBase/EnginePath.h>
#include "EngineSprite.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>

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

	UEngineWindowImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	string UpperName = UEngineString::ToUpper(_KeyName);

	if (Images.contains(UpperName) == true)
		MSGASSERT(nullptr, _Path, "�� �̹� �ε� �� Image �Դϴ�.");
	if (Sprites.contains(UpperName) == true)
		MSGASSERT(nullptr, _Path, "�� �̹� �ε� �� Sprite �Դϴ�.");

	UEngineWindowImage* NewImage = new UEngineWindowImage();
	NewImage->Load(WindowImage, _Path);
	NewImage->SetName(UpperName);
	Images.insert(make_pair(UpperName, NewImage));

	UEngineSprite* NewSprite = new UEngineSprite();
	NewSprite->SetName(UpperName);

	FTransform form = {};
	form.Location = FVector2D(0.f, 0.f);
	form.Scale = NewImage->GetImageScale();

	NewSprite->PushData(NewImage, form);
	Sprites.insert(make_pair(UpperName, NewSprite));
}

void UImageManager::LoadFolder(string_view _KeyName, string_view _Path)
{
	UEnginePath EnginePath = _Path;

	if (EnginePath.IsExists() == false)
		MSGASSERT(nullptr, _Path, "�� ��ȿ���� ���� ���� ����Դϴ�.");

	string UpperName = UEngineString::ToUpper(_KeyName);

	if (Sprites.contains(UpperName))
		MSGASSERT(nullptr, _KeyName, "�� �̹� �ε� �� Image�Դϴ�.");

	UEngineSprite* NewSprite = new UEngineSprite();
	NewSprite->SetName(UpperName);
	Sprites.insert(make_pair(UpperName, NewSprite));

	UEngineWindowImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	UEngineDirectory Dir = _Path;
	vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	string FilePath = {};
	string UpperFileName = {};

	for (size_t i = 0; i < ImageFiles.size(); ++i)
	{
		FilePath = ImageFiles[i].GetPathToString();
		UpperFileName = UEngineString::ToUpper(ImageFiles[i].GetFileName());

		UEngineWindowImage* NewImage = FindImage(UpperFileName);
		if (NewImage == nullptr)
		{
			NewImage = new UEngineWindowImage();
			NewImage->SetName(UpperFileName);
			NewImage->Load(WindowImage, FilePath);
		}
		Images.insert(make_pair(UpperFileName, NewImage));
		
		FTransform Transform = {};
		Transform.Location = { 0.f, 0.f };
		Transform.Scale = NewImage->GetImageScale();

		NewSprite->PushData(NewImage, Transform);
	}
}

UEngineSprite* UImageManager::FindSprite(string_view _KeyName)
{
	if (IsLoadSprite(_KeyName) == false)
		MSGASSERT(nullptr, _KeyName, "�� Load ���� ���� Sprite�Դϴ�.");

	return Sprites[UEngineString::ToUpper(_KeyName)];
}

UEngineWindowImage* UImageManager::FindImage(string_view _KeyName)
{
	string UpperName = UEngineString::ToUpper(_KeyName);

	if (Images.contains(UpperName) == false)
		return nullptr;
	return Images[UpperName];
}

void UImageManager::CutSprite(string_view _KeyName, FVector2D _CuttingSize)
{
	string UpperName = UEngineString::ToUpper(_KeyName);

	if (Sprites.contains(UpperName) == false)
		MSGASSERT(nullptr, _KeyName, "��� �̸��� Sprite�� �������� �ʽ��ϴ�.");
	if (Images.contains(UpperName) == false)
		MSGASSERT(nullptr, _KeyName, "��� �̸��� Image�� �������� �ʽ��ϴ�.");

	UEngineSprite* Sprite = Sprites[UpperName];
	UEngineWindowImage* Image = Images[UpperName];

	Sprite->ClearSpriteData();
	Sprite->SetName(UpperName);
	Image->SetName(UpperName);

	if (Image->GetImageScale().iX() % _CuttingSize.iX() != 0)
		MSGASSERT(nullptr, _KeyName, "�� ����� ��Ȯ���� �ʽ��ϴ�.");
	if (Image->GetImageScale().iY() % _CuttingSize.iY() != 0)
		MSGASSERT(nullptr, _KeyName, "�� ����� ��Ȯ���� �ʽ��ϴ�.");

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
		MSGASSERT(nullptr, "�̹����� ���� ������ 0 �����Դϴ�.");
	if (_ImageCount <= 0)
		MSGASSERT(nullptr, "�� �̹��� ������ 0 �����Դϴ�.");
	if (Sprites.contains(SearchName) == false)
		MSGASSERT(nullptr, _SearchKeyName, "��� �̸��� Sprite�� �ε��� �� �����ϴ�.");
	if (Images.contains(SearchName) == false)
		MSGASSERT(nullptr, _SearchKeyName, "��� �̸��� Image�� �ε��� �� �����ϴ�.");
	if (Sprites.contains(NewSpriteName) == true)
		MSGASSERT(nullptr, _NewSpriteKeyName, "��� �̸��� Sprite�� �̹� �����մϴ�.");
	if (Images.contains(NewSpriteName) == true)
		MSGASSERT(nullptr, _NewSpriteKeyName, "��� �̸��� Image�� �̹� �����մϴ�.");


	UEngineWindowImage* Image = Images[SearchName];

	UINT YCount = _ImageCount / _Xcount;
	if (_ImageCount % _Xcount > 0)
		++YCount;

	float TotalSizeX = _StartPos.X + (_CuttingSize.X * _Xcount) + (_XYOffSet.X * (_Xcount - 1));
	float TotalSizeY = _StartPos.Y + (_CuttingSize.Y * YCount) + (_XYOffSet.Y * (YCount - 1));

	if (TotalSizeX > Image->GetImageScale().X)
		MSGASSERT(nullptr, "�ʿ��� �̹��� ���� ����� ���� �̹��� ������� Ů�ϴ�.");
	if (TotalSizeY > Image->GetImageScale().Y)
		MSGASSERT(nullptr, "�ʿ��� �̹��� ���� ����� ���� �̹��� ������� Ů�ϴ�.");

	UEngineSprite* NewSprite = new UEngineSprite();
	
	NewSprite->ClearSpriteData();
	NewSprite->SetName(NewSpriteName);

	Sprites.insert(make_pair(NewSpriteName, NewSprite));

	FVector2D CuttingPos = {};

	for (UINT y = 0; y < YCount; ++y)
	{
		CuttingPos.Y = _StartPos.Y + _CuttingSize.Y * y + _XYOffSet.Y * y;

		for (UINT x = 0; x < _Xcount; ++x)
		{
			CuttingPos.X = _StartPos.X + _CuttingSize.X * x + _XYOffSet.X * x;
			FTransform insertInst = {};
			insertInst.Scale = _CuttingSize;
			insertInst.Location = CuttingPos;
			NewSprite->PushData(Image, insertInst);
		}
		CuttingPos.X = 0.f;
	}
}

