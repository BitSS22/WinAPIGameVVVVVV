#pragma once

// Ό³Έν :
class UEngineSprite : public UObject
{
public:
	INNER_CLASS class USpriteData;
public:
	UEngineSprite();
	~UEngineSprite();

	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

private:
	vector<USpriteData> Data = {};

public:
	void PushData(UEngineWindowImage* _Image, const FTransform& _Trans);
	void ClearSpriteData()
	{
		Data.clear();
	}

private:

public:
	USpriteData GetSpriteData(int _Index)
	{
		return Data[_Index];
	}

public:
	INNER_CLASS class USpriteData
	{
	public:
		UEngineWindowImage* Image = {};
		FTransform Transform = {};
	};
};

