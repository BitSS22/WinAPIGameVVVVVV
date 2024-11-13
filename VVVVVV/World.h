#pragma once
#include "Room.h"
#include <EngineBase/EngineSerializer.h>

// Ό³Έν :
class AWorld : public AActor
{
public:
	friend class ATileMapEditorMode;
	friend class ARoom;
	friend class ABackGround;
	INNER_CLASS struct RoomData;
	INNER_CLASS struct RoomTileData;
	INNER_CLASS struct EntityData;
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
	bool EditMode = true;

public:
	virtual void BeginPlay() override;

	void SaveFile();
	void LoadFile();

private:

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
	void SetEditMode(bool _Value)
	{
		EditMode = _Value;
	}

public:
	INNER_CLASS struct EntityData : public ISerializObject
	{
		std::string Name = "Debug Tile";
		FVector2D DefualtLocation = {};
		FVector2D DefualtDir = FVector2D::ZERO;
		float Speed = EGameConst::DefualtSpeed;
		float MoveLenght = EGameConst::DefualtMoveLen;
		float MoveLenghtOffset = 0.f;

	public:
		void Serialize(UEngineSerializer& _Class) override;
		void DeSerialize(UEngineSerializer& _Class) override;
	};

	INNER_CLASS struct RoomTileData : public ISerializObject
	{
	public:
		std::string Name = "None Tile";
		int SpriteIndex = 0;
		bool ShowTile = false;

	public:
		void Serialize(UEngineSerializer& _Class) override;
		void DeSerialize(UEngineSerializer& _Class) override;
	};

	INNER_CLASS struct RoomBackGroundData : public ISerializObject
	{
	public:
		std::string Name = "Debug BackGround.png";
		int SpriteIndex = 0;
		bool Effect = false;

	public:
		void Serialize(UEngineSerializer& _Class) override;
		void DeSerialize(UEngineSerializer& _Class) override;
	};

	INNER_CLASS struct RoomData : public ISerializObject
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
		std::string RoomBackGroundData = "Debug BackGround.png";
		std::vector<EntityData> EntityDatas = {};
		bool LoopRoom = false;

		FIntPoint TileCount = EGameConst::TileCount;
		FIntPoint TileScale = EGameConst::TileScale;

	public:
		virtual void Serialize(UEngineSerializer& _Class) override;
		virtual void DeSerialize(UEngineSerializer& _Class) override;
	};

};

