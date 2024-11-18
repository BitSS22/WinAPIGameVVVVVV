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
	ETileType TileType = ETileType::Last;

public:	
	virtual void BeginPlay() override;

	void SetTile(const AGameWorld::RoomData::RoomTileData& _Data);
	AGameWorld::RoomData::RoomTileData GetTileData();

private:
	void AnimationTileSetup();

public:

	ETileType GetTileType()
	{
		return TileType;
	}

};

