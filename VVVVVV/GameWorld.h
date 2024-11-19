#pragma once
#include <EngineBase/EngineSerializer.h>
#include "GameConst.h"
#include <string>
#include <vector>
#include "Enums.h"
#include <EngineBase/EngineMath.h>

class ARoom;

struct RoomTileData : public ISerializObject
{
public:
	std::string Name = "NoneTiles::None";
	int CurIndex = 0;
	ETileType TileType = ETileType::None;

public:
	void Serialize(UEngineSerializer& _Class) override;
	void DeSerialize(UEngineSerializer& _Class) override;
};

struct RoomBackGroundData : public ISerializObject
{
public:
	std::string Name = "BackGrounds::00 Space";
	int Index = 0;
	EBackGroundType BackGroundType = EBackGroundType::Space;
	float AnimationSpeed = 320.f;

public:
	void Serialize(UEngineSerializer& _Class) override;
	void DeSerialize(UEngineSerializer& _Class) override;
};

struct RoomEntityData : public ISerializObject
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

class RoomData : public ISerializObject
{
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

class AGameWorld : public AActor
{
public:
	AGameWorld();
	~AGameWorld();

	AGameWorld(const AGameWorld& _Other) = delete;
	AGameWorld(AGameWorld&& _Other) noexcept = delete;
	AGameWorld& operator=(const AGameWorld& _Other) = delete;
	AGameWorld& operator=(AGameWorld&& _Other) noexcept = delete;

private:
	ARoom* Room = nullptr;
	std::vector<std::vector<RoomData>> RoomDatas = {};

public:
	virtual void BeginPlay() override;

	void SaveRoomData();

	void SaveMapDataFile();
	void LoadMapDataFile();

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

};

