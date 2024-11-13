#pragma once
#include <EnginePlatform/EngineWindowImage.h>
#include "World.h"

class AEntity;
class ABackGround;
class AWorld;

class ARoom : public AActor
{
public:
	friend class ATileMapEditorMode;
	friend class AWorld;
	friend class ABackGround;
public:
	ARoom();
	ARoom(FIntPoint _TileCount, FIntPoint _TileScale);
	~ARoom();

	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

private:
	FIntPoint TileCount = EGameConst::TileCount;
	FIntPoint TileScale = EGameConst::TileScale;
	std::vector<std::vector<USpriteRenderer*>> Tiles = {};
	std::vector<std::vector<USpriteRenderer*>> BackGroundTiles = {};
	ABackGround* BackGround = nullptr;
	std::vector<AEntity*> Entites = {};
	AWorld* World = nullptr;

public:
	virtual void BeginPlay() override;

	void MoveRoom(FIntPoint _Index);
	void SaveRoomData();
	void LoadRoomData(FIntPoint _Index);

	void SetupAnimationTiles();

private:

public:
	FIntPoint GetOnTileIndex(FIntPoint _Pos)
	{
		return FIntPoint(_Pos.X / TileScale.X, _Pos.Y / TileScale.Y);
	}

};

