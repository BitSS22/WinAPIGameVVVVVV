#pragma once
#include "Room.h"
#include <EngineBase/EngineSerializer.h>

// Ό³Έν :
class AGameWorld : public AActor
{
public:
	INNER_CLASS struct RoomData;
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

	void SaveRoomData();

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
	INNER_CLASS struct RoomData : public ISerializObject
	{
	public:
		INNER_CLASS struct RoomEntityData : public ISerializObject
		{
			std::string Name = "Debug Tile";
			EEntityType EntityType = EEntityType::Last;
			FVector2D DefualtLocation = FVector2D::ZERO;
			FVector2D DefualtDir = FVector2D::ZERO;
			float Speed = 128.f;
			float MoveLenght = 128.f;
			float MoveLenghtOffset = 0.f;

		public:
			void Serialize(UEngineSerializer& _Class) override;
			void DeSerialize(UEngineSerializer& _Class) override;
		};

		INNER_CLASS struct RoomTileData : public ISerializObject
		{
		public:
			std::string Name = "Debug Tile";
			int CurIndex = 0;
			ETileType TileType = ETileType::Last;

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
			float AnimationSpeed = 320.f;

		public:
			void Serialize(UEngineSerializer& _Class) override;
			void DeSerialize(UEngineSerializer& _Class) override;
		};


	public:
		RoomData()
		{
			TileDatas.resize(EGameConst::TileCount.Y);
			for (size_t y = 0; y < TileDatas.size(); ++y)
				TileDatas[y].resize(EGameConst::TileCount.X);
		}

	public:
		std::vector<std::vector<RoomTileData>> TileDatas = {};
		RoomBackGroundData BackGroundData = {};
		std::vector<RoomEntityData> EntityDatas = {};
		bool LoopRoom = false;

	public:
		virtual void Serialize(UEngineSerializer& _Class) override;
		virtual void DeSerialize(UEngineSerializer& _Class) override;

	};

};

