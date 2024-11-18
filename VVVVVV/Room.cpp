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
	BackGroundTiles.resize(EGameConst::TileCount.Y);
	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		BackGroundTiles[y].reserve(EGameConst::TileCount.X);
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			BackGroundTiles[y][x] = GetWorld()->SpawnActor<ATile>();
			BackGroundTiles[y][x]->SetActorLocation(FVector2D(EGameConst::TileScale.X * x + EGameConst::TileScale.X / 2, EGameConst::TileScale.Y * y + EGameConst::TileScale.Y / 2));
		}
	}

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
	SaveRoomData();

	if (_Index.X < 0)
		_Index.X = GameWorld->WorldMaxIndex.X - 1;
	else if (_Index.X >= GameWorld->WorldMaxIndex.X)
		_Index.X = 0;
	if (_Index.Y < 0)
		_Index.Y = GameWorld->WorldMaxIndex.Y - 1;
	else if (_Index.Y >= GameWorld->WorldMaxIndex.Y)
		_Index.Y = 0;

	LoadRoomData(_Index);

	GameWorld->CurRoomIndex = _Index;
}

void ARoom::SaveRoomData()
{
	if (GameWorld->EditMode == false)
		return;

	auto& CurRoomDatas = GameWorld->RoomDatas[GameWorld->CurRoomIndex.Y][GameWorld->CurRoomIndex.X];

	for (size_t y = 0; y < TileCount.Y; ++y)
	{
		for (size_t x = 0; x < TileCount.X; ++x)
		{
			AGameWorld::RoomTileData TileData = {};
			TileData.Name = Tiles[y][x]->GetCurSpriteName();
			TileData.SpriteIndex = Tiles[y][x]->GetCurIndex();
			if (TileData.Name.find("NONE TILE") != std::string::npos)
				TileData.ShowTile = false;
			else
				TileData.ShowTile = true;
			CurRoomDatas.RoomTileDatas[y][x] = TileData;

			AGameWorld::RoomTileData BackGroundTileData = {};
			BackGroundTileData.Name = BackGroundTiles[y][x]->GetCurSpriteName();
			BackGroundTileData.SpriteIndex = BackGroundTiles[y][x]->GetCurIndex();
			if (TileData.Name.find("SPIKETILES::") != std::string::npos)
				BackGroundTileData.ShowTile = true;
			else if (BackGroundTileData.Name.find("NONE TILE") != std::string::npos || TileData.Name.find("NONE TILE") == std::string::npos)
				BackGroundTileData.ShowTile = false;
			else
				BackGroundTileData.ShowTile = true;
			CurRoomDatas.RoomBackGroundTileDatas[y][x] = BackGroundTileData;
		}
	}

	CurRoomDatas.RoomBackGroundData = BackGround->Sprite->GetCurSpriteName();

	CurRoomDatas.EntityDatas.clear();

	for (size_t i = 0; i < Entites.size(); ++i)
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

void ARoom::LoadRoomData(FIntPoint _Index)
{
	auto& ChangeRoomDatas = GameWorld->RoomDatas[_Index.Y][_Index.X];

	for (size_t y = 0; y < TileCount.Y; ++y)
	{
		for (size_t x = 0; x < TileCount.X; ++x)
		{
			Tiles[y][x]->SetSprite(ChangeRoomDatas.RoomTileDatas[y][x].Name, ChangeRoomDatas.RoomTileDatas[y][x].SpriteIndex);
			Tiles[y][x]->SetActive(ChangeRoomDatas.RoomTileDatas[y][x].ShowTile);
			BackGroundTiles[y][x]->SetSprite(ChangeRoomDatas.RoomBackGroundTileDatas[y][x].Name, ChangeRoomDatas.RoomBackGroundTileDatas[y][x].SpriteIndex);
			BackGroundTiles[y][x]->SetActive(ChangeRoomDatas.RoomBackGroundTileDatas[y][x].ShowTile);
		}
	}

	if (GameWorld->EditMode == true)
	{
		for (size_t y = 0; y < TileCount.Y; ++y)
		{
			for (size_t x = 0; x < TileCount.X; ++x)
			{
				Tiles[y][x]->SetActive(true);
				BackGroundTiles[y][x]->SetActive(true);
			}
		}
	}


	for (size_t i = 0; i < Entites.size(); ++i)
		Entites[i]->Destroy();
	Entites.clear();

	if (BackGround->Sprite != nullptr)
		BackGround->SetBackGround(ChangeRoomDatas.RoomBackGroundData);

	LoopRoom = ChangeRoomDatas.LoopRoom;

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
