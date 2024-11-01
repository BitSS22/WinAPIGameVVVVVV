#include "pch.h"
#include "TileMapEditorMode.h"
#include "Player.h"

ATileMapEditorMode::ATileMapEditorMode()
{
}

ATileMapEditorMode::~ATileMapEditorMode()
{
}

void ATileMapEditorMode::BeginPlay()
{
	Super::BeginPlay();

	Tiles.resize(TileCountY);

	for (int y = 0; y < TileCountY; ++y)
	{
		Tiles[y].reserve(TileCountX);

		for (int x = 0; x < TileCountX; ++x)
		{
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetSprite("NoneTile", 0);
			NewSprite->SetName("NoneTile");
			NewSprite->SetComponentScale(FVector2D(TileSizeX, TileSizeY));
			NewSprite->SetComponentLocation(FVector2D(TileSizeX * x + TileSizeX / 2, TileSizeY * y + TileSizeY / 2));
			Tiles[y].push_back(NewSprite);
		}
	}
}
enum class TILE_TYPE
{
	CLOSE_TOP_LEFT = 0,
	CLOSE_TOP,
	CLOSE_TOP_RIGHT,
	OPEN_BOTTOM,
	CLOSE_LEFT,
	OPEN,
	CLOSE_RIGHT,
	CLOSE_LEFT_RIGHT,
	CLOSE_LEFT_BOTTOM,
	CLOSE_BOTTOM,
	CLOSE_RIGHT_BOTTOM,
	OPEN_TOP,
	OPEN_RIGHT,
	CLOSE_TOP_BOTTOM,
	OPEN_LEFT,
	CLOSE,
	NONE_TILE
};

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	POINT CursorPos = {};
	GetCursorPos(&CursorPos);
	ScreenToClient(UEngineAPICore::GetCore()->GetMainWindow().GetWindowHandle(), &CursorPos);

	if (KEY_PRESS(VK_LBUTTON) == true)
	{
		FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
		if (CursorPos.x < 0 || CursorPos.y < 0 || CursorPos.x >= WindowSize.X || CursorPos.y >= WindowSize.Y)
			return;

		int XTileIndex = CursorPos.x / TileSizeX;
		int YTileIndex = CursorPos.y / TileSizeY;

		for (int y = YTileIndex - 1; y <= YTileIndex + 1; ++y)
		{
			for (int x = XTileIndex - 1; x <= XTileIndex + 1; ++x)
			{
				if (IsTile(x, y) == true)
				{
					int a = 0;
				}
			}
		}


		// Tiles[CursorPos.y / TileSizeY][CursorPos.x / TileSizeX]->SetSprite("Tiles", 5);
	}
}

bool ATileMapEditorMode::IsTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= TileCountX || y >= TileCountY)
		return true;
	else if (Tiles[y][x]->GetName() == string("NoneTile"))
		return false;
	
	return true;
}