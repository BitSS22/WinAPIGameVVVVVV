#include "pch.h"
#include "World.h"
#include "Room.h"
#include "BackGround.h"
#include "Entity.h"
#include "MoveEntity.h"
#include "EngineBase/EngineDirectory.h"
#include <EngineBase/EngineFile.h>

AWorld::AWorld()
{
}

AWorld::~AWorld()
{
}

void AWorld::BeginPlay()
{
	Room = GetWorld()->SpawnActor<ARoom>();

	RoomDatas.resize(WorldMaxIndex.Y);
	for (size_t y = 0; y < RoomDatas.size(); ++y)
		RoomDatas[y].resize(WorldMaxIndex.X);

	GetWorld()->SetCameraToMainPawn(false);
}

void AWorld::MoveRoom(FIntPoint _Index)
{
	SaveRoomData();

	if (_Index.X < 0)
		_Index.X = WorldMaxIndex.X - 1;
	else if (_Index.X >= WorldMaxIndex.X)
		_Index.X = 0;
	if (_Index.Y < 0)
		_Index.Y = WorldMaxIndex.Y - 1;
	else if (_Index.Y >= WorldMaxIndex.Y)
		_Index.Y = 0;

	LoadRoomData(_Index);

	CurRoomIndex = _Index;
}

void AWorld::SaveRoomData()
{
	if (EditMode == false)
		return;

	auto& CurRoomDatas = RoomDatas[CurRoomIndex.Y][CurRoomIndex.X];

	for (size_t y = 0; y < Room->TileCount.Y; ++y)
	{
		for (size_t x = 0; x < Room->TileCount.X; ++x)
		{
			RoomTileData TileData = {};
			TileData.Name = Room->Tiles[y][x]->GetCurSpriteName();
			TileData.SpriteIndex = Room->Tiles[y][x]->GetCurIndex();
			if (TileData.Name.find("NONE TILE") != std::string::npos)
				TileData.ShowTile = false;
			else
				TileData.ShowTile = true;
			CurRoomDatas.RoomTileDatas[y][x] = TileData;

			RoomTileData BackGroundTileData = {};
			BackGroundTileData.Name = Room->BackGroundTiles[y][x]->GetCurSpriteName();
			BackGroundTileData.SpriteIndex = Room->BackGroundTiles[y][x]->GetCurIndex();
			if (BackGroundTileData.Name.find("NONE TILE") != std::string::npos || TileData.ShowTile == true)
				BackGroundTileData.ShowTile = false;
			else
				BackGroundTileData.ShowTile = true;
			CurRoomDatas.RoomBackGroundTileDatas[y][x] = BackGroundTileData;
		}
	}

	CurRoomDatas.RoomBackGroundData = Room->BackGround->Sprite->GetCurSpriteName();

	CurRoomDatas.EntityDatas.clear();

	for (size_t i = 0; i < GetRoom()->Entites.size(); ++i)
	{
		EntityData EntityData = {};
		AEntity* Entity = GetRoom()->Entites[i];

		EntityData.Name = Entity->GetRenderer()->GetCurSpriteName();
		EntityData.DefualtLocation = Entity->GetActorLocation();

		AMoveEntity* MoveEntity = dynamic_cast<AMoveEntity*>(Entity);

		if (MoveEntity != nullptr)
		{
			EntityData.DefualtLocation = MoveEntity->GetEntityDefualtLocation();
			EntityData.DefualtDir = MoveEntity->GetEntityDefualtDir();
			EntityData.Speed = MoveEntity->GetSpeed();
			EntityData.MoveLenght = MoveEntity->GetMoveLenght();
			EntityData.MoveLenghtOffset = MoveEntity->GetMoveLenghtOffset();
		}

		CurRoomDatas.EntityDatas.push_back(EntityData);

		Entity->Destroy();
	}

	GetRoom()->Entites.clear();
}

void AWorld::LoadRoomData(FIntPoint _Index)
{
	auto& ChangeRoomDatas = RoomDatas[_Index.Y][_Index.X];

	for (size_t y = 0; y < Room->TileCount.Y; ++y)
	{
		for (size_t x = 0; x < Room->TileCount.X; ++x)
		{
			Room->Tiles[y][x]->SetSprite(ChangeRoomDatas.RoomTileDatas[y][x].Name, ChangeRoomDatas.RoomTileDatas[y][x].SpriteIndex);
			Room->Tiles[y][x]->SetActive(ChangeRoomDatas.RoomTileDatas[y][x].ShowTile);
			Room->BackGroundTiles[y][x]->SetSprite(ChangeRoomDatas.RoomBackGroundTileDatas[y][x].Name, ChangeRoomDatas.RoomBackGroundTileDatas[y][x].SpriteIndex);
			Room->BackGroundTiles[y][x]->SetActive(ChangeRoomDatas.RoomBackGroundTileDatas[y][x].ShowTile);
		}
	}

	if (EditMode == true)
	{
		for (size_t y = 0; y < Room->TileCount.Y; ++y)
		{
			for (size_t x = 0; x < Room->TileCount.X; ++x)
			{
				Room->Tiles[y][x]->SetActive(true);
				Room->BackGroundTiles[y][x]->SetActive(true);
			}
		}
	}

	GetRoom()->BackGround->SetBackGround(ChangeRoomDatas.RoomBackGroundData);

	for (size_t i = 0; i < ChangeRoomDatas.EntityDatas.size(); ++i)
	{
		EntityData Data = ChangeRoomDatas.EntityDatas[i];

		if (ChangeRoomDatas.EntityDatas[i].Name.find("ENEMIES::") != std::string::npos || ChangeRoomDatas.EntityDatas[i].Name.find("PLATFORMS::") != std::string::npos)
		{
			AMoveEntity* NewEntity = GetWorld()->SpawnActor<AMoveEntity>();
			NewEntity->MoveEntityDefaultSetUp(Data.Name, Data.DefualtLocation, Data.DefualtDir, Data.Speed, Data.MoveLenght, Data.MoveLenghtOffset);
			GetRoom()->Entites.push_back(NewEntity);
		}
		else if (ChangeRoomDatas.EntityDatas[i].Name.find("INTEROBJECT::") != std::string::npos)
		{
			AEntity* NewEntity = GetWorld()->SpawnActor<AEntity>();
			NewEntity->EntityDefaultSetUp(Data.Name, Data.DefualtLocation);
			GetRoom()->Entites.push_back(NewEntity);
		}
		else
			MSGASSERT(nullptr, Data.Name, "의 Entity Data를 제대로 로드하지 못했습니다.");
	}
}

void AWorld::SaveFile()
{
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

void AWorld::LoadFile()
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

void AWorld::RoomData::Serialize(UEngineSerializer& _Class)
{
	_Class << RoomTileDatas;
	_Class << RoomBackGroundTileDatas;
	_Class << RoomBackGroundData;
	_Class << EntityDatas;
	_Class << TileCount;
	_Class << TileScale;
}

void AWorld::RoomData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> RoomTileDatas;
	_Class >> RoomBackGroundTileDatas;
	_Class >> RoomBackGroundData;
	_Class >> EntityDatas;
}

void AWorld::EntityData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << DefualtLocation;
	_Class << DefualtDir;
	_Class << Speed;
	_Class << MoveLenght;
	_Class << MoveLenghtOffset;
}

void AWorld::EntityData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> DefualtLocation;
	_Class >> DefualtDir;
	_Class >> Speed;
	_Class >> MoveLenght;
	_Class >> MoveLenghtOffset;
}

void AWorld::RoomTileData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << SpriteIndex;
	_Class << ShowTile;
}

void AWorld::RoomTileData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> SpriteIndex;
	_Class >> ShowTile;
}

void AWorld::RoomBackGroundData::Serialize(UEngineSerializer& _Class)
{
	_Class << Name;
	_Class << SpriteIndex;
	_Class << Effect;
}

void AWorld::RoomBackGroundData::DeSerialize(UEngineSerializer& _Class)
{
	_Class >> Name;
	_Class >> SpriteIndex;
	_Class >> Effect;
}
