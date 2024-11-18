#include "pch.h"
#include "GameWorld.h"
#include "Room.h"
#include "BackGround.h"
#include "Entity.h"
#include "PistonEntity.h"
#include "EngineBase/EngineDirectory.h"
#include <EngineBase/EngineFile.h>

AGameWorld::AGameWorld()
{
}

AGameWorld::~AGameWorld()
{
}

void AGameWorld::BeginPlay()
{
	Room = GetWorld()->SpawnActor<ARoom>();
	Room->GameWorld = this;

	RoomDatas.resize(EGameConst::WorldMaxIndex.Y);
	for (size_t y = 0; y < RoomDatas.size(); ++y)
		RoomDatas[y].resize(EGameConst::WorldMaxIndex.X);

	GetWorld()->SetCameraToMainPawn(false);
}

void AGameWorld::SaveFile()
{
	Room->SaveRoomData();

	UEngineSerializer Ser = {};

	Ser << RoomDatas;

	UEngineDirectory Dir = {};
	Dir.MoveParentToDirectory("Resources");
	Dir.Append("MapData");
	string SaveFileName = Dir.GetPathToString() + "\\MapData.data";
	UEngineFile NewFile = SaveFileName;
	NewFile.FileOpen("wb");
	NewFile.Write(Ser);
}

void AGameWorld::LoadFile()
{
	UEngineSerializer Ser = {};

	UEngineDirectory Dir = {};
	Dir.MoveParentToDirectory("Resources");
	Dir.Append("MapData");
	string LoadFileName = Dir.GetPathToString() + "\\MapData.data";
	UEngineFile NewFile = LoadFileName;
	NewFile.FileOpen("rb");
	NewFile.Read(Ser);

	Ser >> RoomDatas;
}

void AGameWorld::RoomData::Serialize(UEngineSerializer& _Class)
{
	_Class << RoomTileDatas;
	_Class << RoomBackGroundTileDatas;
	_Class << RoomBackGroundData;
	_Class << EntityDatas;
	_Class << LoopRoom;
	_Class << TileCount;
	_Class << TileScale;
}

void AGameWorld::RoomData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> RoomTileDatas;
	_Class >> RoomBackGroundTileDatas;
	_Class >> RoomBackGroundData;
	_Class >> EntityDatas;
	_Class >> LoopRoom;
	_Class >> TileCount;
	_Class >> TileScale;
}

void AGameWorld::RoomEntityData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << DefualtLocation;
	_Class << DefualtDir;
	_Class << Speed;
	_Class << MoveLenght;
	_Class << MoveLenghtOffset;
}

void AGameWorld::RoomEntityData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> DefualtLocation;
	_Class >> DefualtDir;
	_Class >> Speed;
	_Class >> MoveLenght;
	_Class >> MoveLenghtOffset;
}

void AGameWorld::RoomTileData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << SpriteIndex;
	_Class << ShowTile;
}

void AGameWorld::RoomTileData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> SpriteIndex;
	_Class >> ShowTile;
}

void AGameWorld::RoomBackGroundData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << SpriteIndex;
	_Class << Effect;
}

void AGameWorld::RoomBackGroundData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> SpriteIndex;
	_Class >> Effect;
}
