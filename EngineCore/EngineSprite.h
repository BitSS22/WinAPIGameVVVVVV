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
	int SpriteCount = 0;

public:
	void PushData(UEngineWindowImage* _Image, const FTransform& _Trans);
	void ClearSpriteData()
	{
		Data.clear();
		SpriteCount = 0;
	}

private:

public:
	USpriteData GetSpriteData(int _Index) const
	{
		if (_Index >= Data.size())
			MSGASSERT(nullptr, GetNameView(), " Sprite Index overflow.");
		return Data[_Index];
	}
	int GetSpriteCount() const
	{
		return SpriteCount;
	}

public:
	INNER_CLASS class USpriteData
	{
	public:
		UEngineWindowImage* Image = {};
		FTransform Transform = {};
	};
};

