#pragma once
#include "Room.h"
#include <EngineBase/EngineSerializer.h>

// Ό³Έν :
class AGameWorld : public AActor
{
public:
	friend class ATileMapEditorMode;
	friend class ARoom;
	friend class ABackGround;
	INNER_CLASS struct RoomData;
	INNER_CLASS struct RoomTileData;
	INNER_CLASS struct RoomEntityData;
public:
	AGameWorld();
	~AGameWorld();

	AGameWorld(const AGameWorld& _Other) = delete;
	AGameWorld(AGameWorld&& _Other) noexcept = delete;
	AGameWorld& operator=(const AGameWorld& _Other) = delete;
	AGameWorld& operator=(AGameWorld&& _Other) noexcept = delete;

private:
	ARoom* Room = {};
	std::vector<std::vector<RoomData>> RoomDatas = {};

public:
	virtual void BeginPlay() override;

	void SaveFile();
	void LoadFile();

private:

public:
	ARoom* GetRoom() const
	{
		return Room;
	}
	const RoomData& GetRoomDatasRef(FIntPoint _Index) const
	{
		return RoomDatas[_Index.Y][_Index.X];
	}

public:
	INNER_CLASS struct RoomEntityData : public ISerializObject
	{
		std::string Name = "Debug Tile";
		EEntityType EntityType = EEntityType::Last;
		FVector2D DefualtLocation = FVector2D::ZERO;
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
		int Index = 0;
		ETileType TileType = ETileType::Last;
		bool ShowTile = false;

	public:
		void Serialize(UEngineSerializer& _Class) override;
		void DeSerialize(UEngineSerializer& _Class) override;
	};

	INNER_CLASS struct RoomBackGroundData : public ISerializObject
	{
	public:
		std::string Name = "Debug BackGround.png";
		int Index = 0;
		EBackGroundType BackGroundType = EBackGroundType::Last;
		float AnimationSpeed = 0.f;
		bool IsEffect = false;

	public:
		void Serialize(UEngineSerializer& _Class) override;
		void DeSerialize(UEngineSerializer& _Class) override;
	};

	INNER_CLASS struct RoomData : public ISerializObject
	{
		RoomData()
		{
			RoomTileDatas.resize(EGameConst::TileCount.Y);
			for (size_t y = 0; y < RoomTileDatas.size(); ++y)
			{
				RoomTileDatas[y].resize(EGameConst::TileCount.X);
			}

			RoomBackGroundTileDatas.resize(EGameConst::TileCount.Y);
			for (size_t y = 0; y < RoomBackGroundTileDatas.size(); ++y)
			{
				RoomBackGroundTileDatas[y].resize(EGameConst::TileCount.X);
			}
		}

	public:
		std::vector<std::vector<RoomTileData>> RoomTileDatas = {};
		std::vector<std::vector<RoomTileData>> RoomBackGroundTileDatas = {};
		RoomBackGroundData BackGroundData = {};
		std::vector<RoomEntityData> EntityDatas = {};
		bool LoopRoom = false;

	public:
		virtual void Serialize(UEngineSerializer& _Class) override;
		virtual void DeSerialize(UEngineSerializer& _Class) override;
	};

};

