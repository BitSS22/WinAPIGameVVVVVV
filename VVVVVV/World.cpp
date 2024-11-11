#include "pch.h"
#include "World.h"
#include "Room.h"
#include "BackGround.h"

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
	
	Room->BackGround->SetBackGround(ChangeRoomDatas.RoomBackGroundData);

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
}
