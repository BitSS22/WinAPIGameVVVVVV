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
	std::string BGMName = {};

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
	static ARoom* Room;
	static FIntPoint CurRoomIndex;
	static std::vector<std::vector<RoomData>> RoomDatas;

public:
	virtual void BeginPlay() override;

	virtual void LevelChangeStart() override;

	static void SaveRoomData();

	static void SaveMapFile();
	static void LoadMapFile();

private:

public:
	static ARoom* GetRoom()
	{
		return Room;
	}
	static const RoomData& GetRoomDatasRef(FIntPoint _Index)
	{
		return RoomDatas[_Index.Y][_Index.X];
	}
	static FIntPoint GetCurRoomIndex()
	{
		return CurRoomIndex;
	}
	static void SetCurRoomIndex(FIntPoint _Index)
	{
		CurRoomIndex = _Index;
	}

};

