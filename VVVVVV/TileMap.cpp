#include "pch.h"
#include "TileMap.h"

ATileMap::ATileMap()
{
}

ATileMap::ATileMap(FIntPoint _TileCount, FIntPoint _TileScale)
	: TileCount(_TileCount)
	, TileScale (_TileScale)
{
}

ATileMap::~ATileMap()
{
}

void ATileMap::BeginPlay()
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
			NewSprite->SetComponentScale(FVector2D(TileScale.X, TileScale.Y));
			NewSprite->SetComponentLocation(FVector2D(TileScale.X * x + TileScale.X / 2, TileScale.Y * y + TileScale.Y / 2));
			NewSprite->SetSprite("Tile None", 0);
			BackGroundTiles[y].push_back(NewSprite);
		}
	}
}

