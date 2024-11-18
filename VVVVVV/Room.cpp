#include "pch.h"
#include "Room.h"
#include "BackGround.h"
#include "GameWorld.h"
#include "Entity.h"
#include "PistonEntity.h"
#include "Player.h"

ARoom::ARoom()
{
}

ARoom::~ARoom()
{
}

void ARoom::BeginPlay()
{
	BackGround = GetWorld()->SpawnActor<ABackGround>();

	// 타일 스프라이트
	Tiles.resize(EGameConst::TileCount.Y);
	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		Tiles[y].reserve(EGameConst::TileCount.X);
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Tiles[y][x] = GetWorld()->SpawnActor<ATile>();
			Tiles[y][x]->SetActorLocation(FVector2D(EGameConst::TileScale.X * x + EGameConst::TileScale.X / 2, EGameConst::TileScale.Y * y + EGameConst::TileScale.Y / 2));
		}
	}
}

void ARoom::MoveRoom(FIntPoint _Index)
{
	if (_Index.X < 0)
		_Index.X = EGameConst::WorldMaxIndex.X - 1;
	else if (_Index.X >= EGameConst::WorldMaxIndex.X)
		_Index.X = 0;
	if (_Index.Y < 0)
		_Index.Y = EGameConst::WorldMaxIndex.Y - 1;
	else if (_Index.Y >= EGameConst::WorldMaxIndex.Y)
		_Index.Y = 0;

	LoadRoomData(_Index);

	CurRoomIndex = _Index;
}

void ARoom::LoadRoomData(FIntPoint _Index)
{
	const AGameWorld::RoomData& Data = GetGameWorld()->GetRoomDatasRef(CurRoomIndex);

	for (size_t y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (size_t x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Tiles[y][x]->SetTile(Data.RoomTileDatas[y][x]);
		}
	}

	for (size_t i = 0; i < Entites.size(); ++i)
		Entites[i]->Destroy();
	Entites.clear();

	GetBackGround()->SetBackGround(Data.BackGroundData);
	LoopRoom = Data.LoopRoom;

	// TODO. Entity Load Code
	for (size_t i = 0; i < ChangeRoomDatas.EntityDatas.size(); ++i)
	{
		AGameWorld::RoomEntityData Data = ChangeRoomDatas.EntityDatas[i];

		if (ChangeRoomDatas.EntityDatas[i].Name.find("ENEMIES::") != std::string::npos)
		{
			APistonEntity* NewEntity = GetWorld()->SpawnActor<APistonEntity>();
			NewEntity->MoveEntityDefaultSetUp(Data.Name, Data.DefualtLocation, Data.DefualtDir, Data.Speed, Data.MoveLenght, Data.MoveLenghtOffset);
			Entites.push_back(NewEntity);
			NewEntity->SetRoom(this);
		}
		else if (ChangeRoomDatas.EntityDatas[i].Name.find("PLATFORMS::") != std::string::npos)
		{
			APistonEntity* NewEntity = GetWorld()->SpawnActor<APistonEntity>();
			NewEntity->MoveEntityDefaultSetUp(Data.Name, Data.DefualtLocation, Data.DefualtDir, Data.Speed, Data.MoveLenght, Data.MoveLenghtOffset);
			Entites.push_back(NewEntity);
			NewEntity->SetRoom(this);
		}
		else if (ChangeRoomDatas.EntityDatas[i].Name.find("INTEROBJECT::") != std::string::npos)
		{
			AEntity* NewEntity = GetWorld()->SpawnActor<AEntity>();
			NewEntity->EntityDefaultSetUp(Data.Name, Data.DefualtLocation);
			Entites.push_back(NewEntity);
			NewEntity->SetRoom(this);
		}
		else
			MSGASSERT(nullptr, Data.Name, "의 Entity Data를 제대로 로드하지 못했습니다.");
	}
}
