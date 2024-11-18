#pragma once
#include <EnginePlatform/EngineWindowImage.h>
#include "GameWorld.h"
#include "Tile.h"
#include "BackGround.h"

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
	std::vector<AEntity*> Entites = {};
	FIntPoint CurRoomIndex = {};
	bool LoopRoom = false;

	AGameWorld* GameWorld = nullptr;
	ABackGround* BackGround = nullptr;

public:
	virtual void BeginPlay() override;

	void MoveRoom(FIntPoint _Index);
	
	void LoadRoomData(FIntPoint _Index);

private:

public:
	FIntPoint GetOnTileIndex(FVector2D _Pos) const
	{
		if (_Pos.X < 0)
			_Pos.X -= EGameConst::TileScale.X;
		if (_Pos.Y < 0)
			_Pos.Y -= EGameConst::TileScale.Y;

		return FIntPoint(_Pos.X / EGameConst::TileScale.X, _Pos.Y / EGameConst::TileScale.Y);
	}
	ETileType GetTileType(FIntPoint _Index) const
	{
		if (_Index.X < 0 || _Index.X >= EGameConst::TileCount.X || _Index.Y < 0 || _Index.Y >= EGameConst::TileCount.Y)
			return ETileType::None;
		else
			return Tiles[_Index.Y][_Index.X]->GetTileType();
	}
	AGameWorld* GetGameWorld() const
	{
		return GameWorld;
	}
	ABackGround* GetBackGround() const
	{
		return BackGround;
	}
	FIntPoint GetCurRoomIndex() const
	{
		return CurRoomIndex;
	}
	bool GetIsLoop() const
	{
		return LoopRoom;
	}

};

