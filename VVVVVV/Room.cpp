#include "pch.h"
#include "Room.h"

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
	// Ÿ�� ��������Ʈ
	Tiles.resize(TileCount.Y);
	for (int y = 0; y < TileCount.Y; ++y)
	{
		Tiles[y].reserve(TileCount.X);
		for (int x = 0; x < TileCount.X; ++x)
		{
			// TODO. ������ �ε��ϴ� �������� ����
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileScale.X, TileScale.Y));
			NewSprite->SetComponentLocation(FVector2D(TileScale.X * x + TileScale.X / 2, TileScale.Y * y + TileScale.Y / 2));
			NewSprite->SetSprite("Debug Tile", 0);
			Tiles[y].push_back(NewSprite);
		}
	}
	BackGroundTiles.resize(TileCount.Y);
	for (int y = 0; y < TileCount.Y; ++y)
	{
		BackGroundTiles[y].reserve(TileCount.X);
		for (int x = 0; x < TileCount.X; ++x)
		{
			// TODO. ������ �ε��ϴ� �������� ����
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileScale.X, TileScale.Y));
			NewSprite->SetComponentLocation(FVector2D(TileScale.X * x + TileScale.X / 2, TileScale.Y * y + TileScale.Y / 2));
			NewSprite->SetSprite("Debug Tile", 0);
			BackGroundTiles[y].push_back(NewSprite);
		}
	}
}

