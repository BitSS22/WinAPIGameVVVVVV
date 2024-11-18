#pragma once
#include <EnginePlatform/EngineWindowImage.h>
#include "GameWorld.h"
#include "Tile.h"

class AEntity;
class ABackGround;
class AGameWorld;
class APlayer;

class ARoom : public AActor
{
public:
	friend class ATileMapEditorMode;
	friend class AGameWorld;
	friend class ABackGround;
public:
	ARoom();
	~ARoom();

	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

private:
	std::vector<std::vector<ATile*>> Tiles = {};
	std::vector<std::vector<ATile*>> BackGroundTiles = {};
	ABackGround* BackGround = nullptr;
	std::vector<AEntity*> Entites = {};
	FIntPoint CurRoonIndex = {};
	bool LoopRoom = false;
	AGameWorld* GameWorld = nullptr;

public:
	virtual void BeginPlay() override;

	void MoveRoom(FIntPoint _Index);
	
	void SaveRoomData();
	void LoadRoomData(FIntPoint _Index);

private:

public:
	FIntPoint GetOnTileIndex(FVector2D _Pos) const
	{
		FIntPoint Result = FIntPoint(_Pos.X / EGameConst::TileScale.X, _Pos.Y / EGameConst::TileScale.Y);
		return Result;
	}
	ETileType GetTileType(FIntPoint _Index) const
	{
		if (_Index.X < 0 || _Index.X >= EGameConst::TileCount.X || _Index.Y < 0 || _Index.Y >= EGameConst::TileCount.Y)
			return ETileType::None;
		return Tiles[_Index.Y][_Index.X]->GetTileType();
	}
	AGameWorld* GetGameWorld() const
	{
		return GameWorld;
	}

};

