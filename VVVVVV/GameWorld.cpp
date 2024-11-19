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
	Room->SetGameWorld(this);

	RoomDatas.resize(EGameConst::WorldMaxIndex.Y);
	for (size_t y = 0; y < RoomDatas.size(); ++y)
		RoomDatas[y].resize(EGameConst::WorldMaxIndex.X);

	GetWorld()->SetCameraToMainPawn(false);
}

void AGameWorld::SaveRoomData()
{
	FIntPoint CurRoomIndex = Room->GetCurRoomIndex();
	AGameWorld::RoomData& Data = RoomDatas[CurRoomIndex.Y][CurRoomIndex.X];

	for (size_t y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (size_t x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Data.TileDatas[y][x] = Room->GetTilesCRef()[y][x]->GetTileData();
		}
	}

	Data.BackGroundData = Room->GetBackGround()->GetBackGroundData();
	Data.LoopRoom = Room->GetIsLoop();

	// TODO. Entity Save Code
	Data.EntityDatas.clear();

	for (size_t i = 0; i < Room->GetEntitesCRef().size(); ++i)
	{
		AGameWorld::RoomEntityData EntityData = {};
		AEntity* Entity = Entites[i];

		EntityData.Name = Entity->GetRenderer()->GetCurSpriteName();
		EntityData.DefualtLocation = Entity->GetActorLocation();

		APistonEntity* MoveEntity = dynamic_cast<APistonEntity*>(Entity);

		if (MoveEntity != nullptr)
		{
			EntityData.DefualtLocation = MoveEntity->GetEntityDefualtLocation();
			EntityData.DefualtDir = MoveEntity->GetEntityDefualtDir();
			EntityData.Speed = MoveEntity->GetSpeed();
			EntityData.MoveLenght = MoveEntity->GetMoveLenght();
			EntityData.MoveLenghtOffset = MoveEntity->GetMoveLenghtOffset();
		}

		CurRoomDatas.EntityDatas.push_back(EntityData);
	}
}

void AGameWorld::SaveFile()
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
