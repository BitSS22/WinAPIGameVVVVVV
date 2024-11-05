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
	// 타일 스프라이트
	BackGroundTiles.resize(TileCount.Y);
	for (int y = 0; y < TileCount.Y; ++y)
	{
		BackGroundTiles[y].reserve(TileCount.X);
		for (int x = 0; x < TileCount.X; ++x)
		{
			// TODO. 파일을 로드하는 내용으로 변경
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileSize.X, TileSize.Y));
			NewSprite->SetComponentLocation(FVector2D(TileSize.X * x + TileSize.X / 2, TileSize.Y * y + TileSize.Y / 2));
			NewSprite->SetSprite("Tile None", 0);
			BackGroundTiles[y].push_back(NewSprite);
		}
	}
}

