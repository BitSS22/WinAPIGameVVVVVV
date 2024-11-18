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
	FIntPoint TileCount = EGameConst::TileCount;
	FIntPoint TileScale = EGameConst::TileScale;
	std::vector<std::vector<ATile*>> Tiles = {};
	std::vector<std::vector<ATile*>> BackGroundTiles = {};
	ABackGround* BackGround = nullptr;
	std::vector<AEntity*> Entites = {};
	AGameWorld* GameWorld = nullptr;
	bool LoopRoom = false;
	APlayer* Player = nullptr;
	bool IsEntityMove = true;

public:
	virtual void BeginPlay() override;

	void MoveRoom(FIntPoint _Index);
	void SaveRoomData();
	void LoadRoomData(FIntPoint _Index);

	void SetupAnimationTiles();

private:

public:
	FIntPoint GetOnTileIndex(FVector2D _Pos)
	{
		FIntPoint Result = FIntPoint(_Pos.X / TileScale.X, _Pos.Y / TileScale.Y);
		return Result;
	}
	AGameWorld* GetGameWorld()
	{
		return GameWorld;
	}
	FIntPoint GetTileCount()
	{
		return TileCount;
	}
	FIntPoint GetTileScale()
	{
		return TileScale;
	}
	std::string GetTileName(FIntPoint _Index)
	{
		if (_Index.X < 0 || _Index.X >= TileCount.X || _Index.Y < 0 || _Index.Y >= TileCount.Y)
			return "NONE TILE";
		return Tiles[_Index.Y][_Index.X]->GetCurSpriteName();
	}
	bool GetIsEntityMove()
	{
		return IsEntityMove;
	}
	void SetIsEntityMove(bool _Value)
	{
		IsEntityMove = _Value;
	}

};

