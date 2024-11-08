#pragma once
#include "Room.h"

// Ό³Έν :
class AWorld : public AActor
{
public:
	friend class ATileMapEditorMode;
	INNER_CLASS struct RoomData;
	INNER_CLASS struct RoomTileData;
public:
	AWorld();
	~AWorld();

	AWorld(const AWorld& _Other) = delete;
	AWorld(AWorld&& _Other) noexcept = delete;
	AWorld& operator=(const AWorld& _Other) = delete;
	AWorld& operator=(AWorld&& _Other) noexcept = delete;

private:
	FIntPoint WorldMaxIndex = EGameConst::WorldMaxIndex;
	FIntPoint CurRoomIndex = { 0, 0 };
	ARoom* Room = {};
	std::vector<std::vector<RoomData>> RoomDatas = {};
	std::vector<std::vector<RoomData>> RoomBackGroundDatas = {};

public:
	virtual void BeginPlay() override;

private:
	void LoadRoomData(FIntPoint _Index);
	void ChangeRoom(FIntPoint _Index);

public:
	ARoom* GetRoom()
	{
		return Room;
	}
	FIntPoint GetWorldSize() const
	{
		return WorldMaxIndex;
	}
	FIntPoint GetCurRoomIndex() const
	{
		return CurRoomIndex;
	}
	void SetCurRoomIndex(FIntPoint _Index)
	{
		CurRoomIndex = _Index;
	}
	bool IsRoomIndexOver(FIntPoint _Index)
	{
		if (_Index.X < 0 || _Index.Y < 0 || _Index.X >= WorldMaxIndex.X, _Index.Y >= WorldMaxIndex.Y)
			return true;
		return false;
	}

public:
	INNER_CLASS struct RoomTileData
	{
	public:
		std::string Name = "Debug Tile";
		int CurSpriteIndex = -1;

	};
	INNER_CLASS struct RoomData
	{
	public:
		std::vector<std::vector<RoomTileData>> RoomTileDatas = {};
		std::vector<std::vector<RoomTileData>> RoomBackGroundTileDatas = {};
		FIntPoint TileCount = {};
		FIntPoint TileScale = {};
	};
};

