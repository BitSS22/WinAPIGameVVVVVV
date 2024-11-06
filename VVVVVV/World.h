#pragma once
#include "Room.h"

// Ό³Έν :
class AWorld : public AActor
{
public:
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
	FIntPoint WorldSize = EGameConst::WorldSize;
	FIntPoint CurRoomIndex = { 0, 0 };
	ARoom* Room = {};
	std::vector<std::vector<RoomData>> RoomDatas = {};
	std::vector<std::vector<RoomData>> RoomBackGroundDatas = {};

public:
	virtual void BeginPlay() override;

private:
	void LoadRoomData(int _X, int _Y);
	void ChangeRoom(FIntPoint _Index);

public:
	ARoom* GetRoom()
	{
		return Room;
	}
	FIntPoint GetWorldSize() const
	{
		return WorldSize;
	}
	FIntPoint GetCurRoomIndex() const
	{
		return CurRoomIndex;
	}
	void SetCurRoomIndex(FIntPoint _Index)
	{
		CurRoomIndex = _Index;
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
	};
};

