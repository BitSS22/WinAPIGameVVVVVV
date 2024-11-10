#include "pch.h"
#include "World.h"
#include "Room.h"

AWorld::AWorld()
{
}

AWorld::~AWorld()
{
}

void AWorld::BeginPlay()
{
	Room = GetWorld()->SpawnActor<ARoom>();

	RoomTileDatas.resize(WorldMaxIndex.Y);
	for (size_t y = 0; y < RoomTileDatas.size(); ++y)
	{
		RoomTileDatas[y].resize(WorldMaxIndex.X);
	}

	RoomBackGroundTileDatas.resize(WorldMaxIndex.X);
	for (size_t y = 0; y < RoomBackGroundTileDatas.size(); ++y)
	{
		RoomBackGroundTileDatas[y].resize(WorldMaxIndex.X);
	}

	RoomBackGroundDatas.resize(WorldMaxIndex.X);
	for (size_t y = 0; y < RoomBackGroundDatas.size(); ++y)
	{
		RoomBackGroundDatas[y].resize(WorldMaxIndex.X);
		for (size_t x = 0; x < RoomBackGroundDatas[y].size(); ++x)
		{
			RoomBackGroundDatas[y][x] = "Debug BackGround.png";
		}
	}
}
