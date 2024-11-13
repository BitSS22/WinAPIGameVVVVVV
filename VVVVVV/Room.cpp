#include "pch.h"
#include "Room.h"
#include "BackGround.h"
#include "GameWorld.h"
#include "Entity.h"
#include "MoveEntity.h"
#include "Player.h"

ARoom::ARoom()
{
}

ARoom::ARoom(FIntPoint _TileCount, FIntPoint _TileScale)
	: TileCount(_TileCount)
	, TileScale(_TileScale)
{
}

ARoom::~ARoom()
{
}

void ARoom::BeginPlay()
{
	BackGround = GetWorld()->SpawnActor<ABackGround>();
	BackGround->Room = this;

	if (GameWorld->EditMode == false)
	{
		Player = GetWorld()->SpawnActor<APlayer>();
		Player->SetRoom(this);
	}

	// 타일 스프라이트
	Tiles.resize(TileCount.Y);
	for (int y = 0; y < TileCount.Y; ++y)
	{
		Tiles[y].reserve(TileCount.X);
		for (int x = 0; x < TileCount.X; ++x)
		{
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileScale.X, TileScale.Y));
			NewSprite->SetComponentLocation(FVector2D(TileScale.X * x + TileScale.X / 2, TileScale.Y * y + TileScale.Y / 2));
			NewSprite->SetSprite("Debug Tile", 0);
			NewSprite->SetOrder(ERenderOrder::TILE);
			Tiles[y].push_back(NewSprite);
		}
	}
	BackGroundTiles.resize(TileCount.Y);
	for (int y = 0; y < TileCount.Y; ++y)
	{
		BackGroundTiles[y].reserve(TileCount.X);
		for (int x = 0; x < TileCount.X; ++x)
		{
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileScale.X, TileScale.Y));
			NewSprite->SetComponentLocation(FVector2D(TileScale.X * x + TileScale.X / 2, TileScale.Y * y + TileScale.Y / 2));
			NewSprite->SetSprite("Debug Tile", 0);
			NewSprite->SetOrder(ERenderOrder::BACKGROUND_TILE);
			BackGroundTiles[y].push_back(NewSprite);
		}
	}
	SetupAnimationTiles();

	LoadRoomData(GameWorld->GetCurRoomIndex());
}

void ARoom::SetupAnimationTiles()
{
	for (int y = 0; y < TileCount.Y; ++y)
	{
		for (int x = 0; x < TileCount.X; ++x)
		{
			Tiles[y][x]->CreateAnimation("AnimationTiles::01 Animation Cyan", "AnimationTiles::01 Animation Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("AnimationTiles::02 Animation Pink", "AnimationTiles::02 Animation Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("AnimationTiles::03 Animation Red", "AnimationTiles::03 Animation Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("AnimationTiles::04 Animation Blue", "AnimationTiles::04 Animation Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("AnimationTiles::05 Animation Yellow", "AnimationTiles::05 Animation Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("AnimationTiles::06 Animation Green", "AnimationTiles::06 Animation Green", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, EGameConst::AnimationTime, true);

			Tiles[y][x]->CreateAnimation("RailTiles::01 Rail Left Cyan", "RailTiles::01 Rail Left Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::02 Rail Left Pink", "RailTiles::02 Rail Left Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::03 Rail Left Red", "RailTiles::03 Rail Left Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::04 Rail Left Blue", "RailTiles::04 Rail Left Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::05 Rail Left Yellow", "RailTiles::05 Rail Left Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::06 Rail Left Green", "RailTiles::06 Rail Left Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::07 Rail Left Grey", "RailTiles::07 Rail Left Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);

			Tiles[y][x]->CreateAnimation("RailTiles::08 Rail Right Cyan", "RailTiles::08 Rail Right Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::09 Rail Right Pink", "RailTiles::09 Rail Right Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::10 Rail Right Red", "RailTiles::10 Rail Right Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::11 Rail Right Blue", "RailTiles::11 Rail Right Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::12 Rail Right Yellow", "RailTiles::12 Rail Right Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::13 Rail Right Green", "RailTiles::13 Rail Right Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
			Tiles[y][x]->CreateAnimation("RailTiles::14 Rail Right Grey", "RailTiles::14 Rail Right Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
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
		AGameWorld::EntityData EntityData = {};
		AEntity* Entity = Entites[i];

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
		AGameWorld::EntityData Data = ChangeRoomDatas.EntityDatas[i];

		if (ChangeRoomDatas.EntityDatas[i].Name.find("ENEMIES::") != std::string::npos || ChangeRoomDatas.EntityDatas[i].Name.find("PLATFORMS::") != std::string::npos)
		{
			AMoveEntity* NewEntity = GetWorld()->SpawnActor<AMoveEntity>();
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
