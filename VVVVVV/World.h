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
	std::vector<std::vector<RoomData>> RoomTileDatas = {};
	std::vector<std::vector<RoomData>> RoomBackGroundTileDatas = {};
	std::vector<std::vector<std::string>> RoomBackGroundDatas = {};

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
		if (_Index.X < 0 || _Index.Y < 0 || _Index.X >= WorldMaxIndex.X || _Index.Y >= WorldMaxIndex.Y)
			return true;
		return false;
	}

public:
	INNER_CLASS struct RoomTileData
	{
	public:
		std::string Name = "Debug Tile";
		int SpriteIndex = 0;

	};
	INNER_CLASS struct RoomBackGroundData
	{
	public:
		std::string Name = "Debug BackGround.png";
		int SpriteIndex = 0;
		bool Effect = false;
	};
	INNER_CLASS struct RoomData
	{
		RoomData()
		{
			RoomTileDatas.resize(TileCount.Y);
			for (size_t y = 0; y < RoomTileDatas.size(); ++y)
			{
				RoomTileDatas[y].resize(TileCount.X);
			}
			RoomBackGroundTileDatas.resize(TileCount.Y);
			for (size_t y = 0; y < RoomBackGroundTileDatas.size(); ++y)
			{
				RoomBackGroundTileDatas[y].resize(TileCount.X);
			}
		}
	public:
		std::vector<std::vector<RoomTileData>> RoomTileDatas = {};
		std::vector<std::vector<RoomTileData>> RoomBackGroundTileDatas = {};
		FIntPoint TileCount = EGameConst::TileCount;
		FIntPoint TileScale = EGameConst::TileScale;
	};
};

