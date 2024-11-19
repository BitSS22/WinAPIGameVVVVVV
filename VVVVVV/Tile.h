#pragma once
#include <EngineCore/SpriteRenderer.h>
#include "GameWorld.h"

// Ό³Έν :
class ATile : public AActor
{
public:
	ATile();
	~ATile();

	ATile(const ATile& _Other) = delete;
	ATile(ATile&& _Other) noexcept = delete;
	ATile& operator=(const ATile& _Other) = delete;
	ATile& operator=(ATile&& _Other) noexcept = delete;

private:
	USpriteRenderer* Sprite = nullptr;
	ETileType TileType = ETileType::None;

public:	
	virtual void BeginPlay() override;

	void SetTile(const RoomTileData& _Data);
	RoomTileData GetTileData();

private:
	void AnimationTileSetup();

public:
	ETileType GetType()
	{
		return TileType;
	}
	std::string GetSpriteName()
	{
		return Sprite->GetCurSpriteName();
	}
	int GetSpriteMaxIndex()
	{
		return Sprite->GetMaxIndex();
	}
	int GetSpriteCurIndex()
	{
		return Sprite->GetCurIndex();
	}
	void AddSpriteIndex(int _Index)
	{
		int Index = Sprite->GetCurIndex();
		Index += _Index;
		if (Index < 0)
			Index = 0;
		else if (Index >= Sprite->GetMaxIndex())
			Index %= Sprite->GetMaxIndex();

		Sprite->SetSprite(Sprite->GetCurSpriteName(), Index);
	}
	void SetSpriteOrder(ERenderOrder _Type)
	{
		Sprite->SetOrder(_Type);
	}

};

