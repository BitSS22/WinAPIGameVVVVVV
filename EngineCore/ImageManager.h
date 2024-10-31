#pragma once
#include <EngineBase/EngineString.h>
#include <EngineBase/EnginePath.h>

class UEngineSprite;

class UImageManager
{
private:
	UImageManager();
public:
	~UImageManager();

	UImageManager(const UImageManager& _Other) = delete;
	UImageManager(UImageManager&& _Other) noexcept = delete;
	UImageManager& operator=(const UImageManager& _Other) = delete;
	UImageManager& operator=(UImageManager&& _Other) noexcept = delete;

private:
	map<string, UEngineWindowImage*> Images = {};
	map<string, UEngineSprite*> Sprites = {};

public:
	void Load(string_view _Path)
	{
		Load(UEnginePath(_Path).GetFileName(), _Path);
	}
	void LoadFolder(string_view _Path)
	{
		LoadFolder(UEnginePath(_Path).GetDirectoryName(), _Path);
	}
	void Load(string_view _KeyName, string_view _Path);
	void LoadFolder(string_view _KeyName, string_view _Path);
	UEngineSprite* FindSprite(string_view _KeyName);
	UEngineWindowImage* FindImage(string_view _KeyName);
	void CutSprite(string_view _KeyName, FVector2D _CuttingSize);
	void CreateCutSprite(string_view _SearchKeyName, string_view _NewSpriteKeyName, FVector2D _StartPos, FVector2D _CuttingSize, FVector2D _XYOffSet, UINT _Xcount, UINT _ImageCount);

private:

public:
	static UImageManager& GetInst()
	{
		static UImageManager Inst = {};
		return Inst;
	}
	bool IsLoadSprite(string_view _KeyName)
	{
		string name = UEngineString::ToUpper(_KeyName);
		return Sprites.contains(name);
	}

};

