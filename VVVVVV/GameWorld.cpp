#include "pch.h"
#include "GameWorld.h"
#include "Room.h"
#include "Tile.h"
#include "BackGround.h"
#include "Entity.h"
#include "PistonEntity.h"
#include "EngineBase/EngineDirectory.h"
#include <EngineBase/EngineFile.h>

ARoom* AGameWorld::Room = nullptr;
FIntPoint AGameWorld::CurRoomIndex = FVector2D::ZERO;
std::vector<std::vector<RoomData>> AGameWorld::RoomDatas = {};

AGameWorld::AGameWorld()
{
}

AGameWorld::~AGameWorld()
{
}

void AGameWorld::BeginPlay()
{
	Room = GetWorld()->SpawnActor<ARoom>();

	RoomDatas.resize(EGameConst::WorldMaxIndex.Y);
	for (size_t y = 0; y < RoomDatas.size(); ++y)
		RoomDatas[y].resize(EGameConst::WorldMaxIndex.X);

	GetWorld()->SetCameraToMainPawn(false);
}

void AGameWorld::LevelChangeStart()
{
	CurRoomIndex = EGameConst::DefualtSaveRoomIndex;
}

void AGameWorld::SaveRoomData()
{
	FIntPoint CurRoomIndex = AGameWorld::GetCurRoomIndex();
	RoomData& Data = RoomDatas[CurRoomIndex.Y][CurRoomIndex.X];

	for (size_t y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (size_t x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Data.TileDatas[y][x] = Room->GetTilesCRef()[y][x]->GetTileData();
		}
	}

	Data.BackGroundData = Room->GetBackGround()->GetBackGroundData();
	Data.LoopRoom = Room->GetIsLoop();
	if (Room->IsBGMEmpty() == false)
		Data.BGMName = Room->GetCurrentSoundName();
	else
		Data.BGMName = "";
	Data.EntityDatas.clear();

	for (size_t i = 0; i < Room->GetEntitesCRef().size(); ++i)
		Data.EntityDatas.push_back(Room->GetEntitesCRef()[i]->GetEntityData());
}

void AGameWorld::SaveMapFile()
{
	SaveRoomData();

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

void AGameWorld::LoadMapFile()
{
	UEngineSerializer Ser = {};

	UEngineDirectory Dir = {};
	Dir.MoveParentToDirectory("Resources");
	Dir.Append("MapData");
	Dir.Append("MapData.data");
	if (Dir.IsExists() == false)
		return;

	string LoadFileName = Dir.GetPathToString();
	UEngineFile NewFile = LoadFileName;
	NewFile.FileOpen("rb");
	NewFile.Read(Ser);

	Ser >> RoomDatas;
}

void RoomEntityData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << EntityType;
	_Class << DefualtLocation;
	_Class << DefualtDir;
	_Class << Speed;
	_Class << MoveLenght;
	_Class << MoveLenghtOffset;
}

void RoomEntityData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> EntityType;
	_Class >> DefualtLocation;
	_Class >> DefualtDir;
	_Class >> Speed;
	_Class >> MoveLenght;
	_Class >> MoveLenghtOffset;
}

void RoomTileData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << CurIndex;
	_Class << TileType;
}

void RoomTileData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> CurIndex;
	_Class >> TileType;
}

void RoomBackGroundData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << Index;
	_Class << BackGroundType;
	_Class << AnimationSpeed;
}

void RoomBackGroundData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> Index;
	_Class >> BackGroundType;
	_Class >> AnimationSpeed;
}

void RoomData::Serialize(UEngineSerializer& _Class)
{
	_Class << TileDatas;
	_Class << BackGroundData;
	_Class << EntityDatas;
	_Class << LoopRoom;
	_Class << BGMName;
}

void RoomData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> TileDatas;
	_Class >> BackGroundData;
	_Class >> EntityDatas;
	_Class >> LoopRoom;
	_Class >> BGMName;
}
