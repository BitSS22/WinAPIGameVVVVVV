#include "pch.h"
#include "TileMapEditorMode.h"

ATileMapEditorMode::ATileMapEditorMode()
{
}

ATileMapEditorMode::~ATileMapEditorMode()
{
}

void ATileMapEditorMode::BeginPlay()
{
	Tiles.resize(TileCountY);


	for (int y = 0; y < TileCountY; ++y)
	{
		Tiles[y].reserve(TileCountX);

		for (int x = 0; x < TileCountX; ++x)
		{
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetSprite("Titles", 7);
			NewSprite->SetComponentScale(FVector2D(TileSizeX, TileSizeY));
			NewSprite->SetComponentLocation(FVector2D(TileSizeX * x + TileSizeX / 2, TileSizeY * y + TileSizeY / 2));
			Tiles[y].push_back(NewSprite);
		}
	}

	Tiles;
}

void ATileMapEditorMode::Tick()
{
}

