#include "pch.h"
#include "TileMap.h"

UTileMap::UTileMap()
{
}

UTileMap::UTileMap(FIntPoint _TileCount, FIntPoint _TileSize)
	: TileCount(_TileCount)
	, TileSize (_TileSize)
{
}

UTileMap::~UTileMap()
{
}

void UTileMap::BeginPlay()
{
	// Ÿ�� ��������Ʈ
	BackGroundTiles.resize(TileCount.Y);
	for (int y = 0; y < TileCount.Y; ++y)
	{
		BackGroundTiles[y].reserve(TileCount.X);
		for (int x = 0; x < TileCount.X; ++x)
		{
			// TODO. ������ �ε��ϴ� �������� ����
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileSize.X, TileSize.Y));
			NewSprite->SetComponentLocation(FVector2D(TileSize.X * x + TileSize.X / 2, TileSize.Y * y + TileSize.Y / 2));
			NewSprite->SetSprite("Tile None", 0);
			BackGroundTiles[y].push_back(NewSprite);
		}
	}
}

