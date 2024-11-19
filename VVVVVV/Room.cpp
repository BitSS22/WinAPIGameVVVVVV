#include "pch.h"
#include "Room.h"
#include "BackGround.h"
#include "GameWorld.h"
#include "Entity.h"
#include "PistonEntity.h"
#include "Player.h"
#include "Enermy.h"
#include "Platform.h"
#include "CheckPoint.h"
#include "Teleport.h"

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

	SetRoom(_Index);

	CurRoomIndex = _Index;
}

void ARoom::SetRoom(FIntPoint _Index)
{
	SetRoom(GetGameWorld()->GetRoomDatasRef(_Index));
}

void ARoom::SetRoom(const AGameWorld::RoomData& _Data)
{
	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Tiles[y][x]->SetTile(_Data.TileDatas[y][x]);
		}
	}

	BackGround->SetBackGround(_Data.BackGroundData);
	LoopRoom = _Data.LoopRoom;

	for (size_t i = 0; i < Entites.size(); ++i)
		Entites[i]->Destroy();
	Entites.clear();

	for (size_t i = 0; i < _Data.EntityDatas.size(); ++i)
	{
		AEntity* NewEntity = nullptr;

		switch (_Data.EntityDatas[i].EntityType)
		{
		case EEntityType::Guy:
			NewEntity = GetWorld()->SpawnActor<AGuy>();
			break;
		case EEntityType::Player:
			NewEntity = GetWorld()->SpawnActor<APlayer>();
			break;
		case EEntityType::Enermy:
			NewEntity = GetWorld()->SpawnActor<AEnermy>();
			break;
		case EEntityType::Platform:
			NewEntity = GetWorld()->SpawnActor<APlatform>();
			break;
		case EEntityType::CheckPoint:
			NewEntity = GetWorld()->SpawnActor<ACheckPoint>();
			break;
		case EEntityType::Teleport:
			NewEntity = GetWorld()->SpawnActor<ATeleport>();
			break;
		}

		if (NewEntity == nullptr)
			MSGASSERT(nullptr, "Spawn Entity Unknown Type.");

		NewEntity->SetEntity(_Data.EntityDatas[i]);
		NewEntity->SetRoom(this);
	}
}

AGameWorld::RoomData ARoom::GetRoomData()
{
	AGameWorld::RoomData Data = {};

	Data.BackGroundData = BackGround->GetBackGroundData();
	Data.LoopRoom = LoopRoom;

	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Data.TileDatas[y][x] = Tiles[y][x]->GetTileData();
		}
	}
	
	for (size_t i = 0; i < Entites.size(); ++i)
		Data.EntityDatas.push_back(Entites[i]->GetEntityData());

	return Data;
}

FIntPoint ARoom::GetOnTileIndex(FVector2D _Pos) const
{
	if (_Pos.X < 0)
		_Pos.X -= EGameConst::TileScale.X;
	if (_Pos.Y < 0)
		_Pos.Y -= EGameConst::TileScale.Y;

	return FIntPoint(_Pos.X / EGameConst::TileScale.X, _Pos.Y / EGameConst::TileScale.Y);
}

ETileType ARoom::GetTileType(FIntPoint _Index) const
{
	if (_Index.X < 0 || _Index.X >= EGameConst::TileCount.X || _Index.Y < 0 || _Index.Y >= EGameConst::TileCount.Y)
		return ETileType::None;
	else
		return Tiles[_Index.Y][_Index.X]->GetTileType();
}
