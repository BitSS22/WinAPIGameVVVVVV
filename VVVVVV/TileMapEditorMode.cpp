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

	CheckTiles.resize(5);
	for (auto& vec : CheckTiles)
		vec.resize(5);

	USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
	NewSprite->SetSprite("Tiles", 5);
	NewSprite->SetComponentScale(FVector2D(TileSizeX, TileSizeY));
	CursorImage = NewSprite;

	Tiles.resize(TileCountY);
	for (int y = 0; y < TileCountY; ++y)
	{
		Tiles[y].reserve(TileCountX);

		for (int x = 0; x < TileCountX; ++x)
		{
			USpriteRenderer* NewSprite = CreateDefaultSubObject<USpriteRenderer>();
			NewSprite->SetComponentScale(FVector2D(TileSizeX, TileSizeY));
			NewSprite->SetComponentLocation(FVector2D(TileSizeX * x + TileSizeX / 2, TileSizeY * y + TileSizeY / 2));
			NewSprite->SetSprite("NoneTile", 0);
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
	DIAGONAL_RIGHT_BOTTOM,
	DIAGONAL_LEFT_BOTTOM,
	CLOSE_LEFT,
	OPEN,
	CLOSE_RIGHT,
	CLOSE_LEFT_RIGHT,
	DIAGONAL_RIGHT_TOP,
	DIAGONAL_LEFT_TOP,
	CLOSE_LEFT_BOTTOM,
	CLOSE_BOTTOM,
	CLOSE_RIGHT_BOTTOM,
	OPEN_TOP,
	POINT_RIGHT_BOTTOM,
	POINT_LEFT_BOTTOM,
	OPEN_RIGHT,
	CLOSE_TOP_BOTTOM,
	OPEN_LEFT,
	CLOSE,
	POINT_RIGHT_TOP,
	POINT_LEFT_TOP,
	NONE_TILE
};

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	GetCursorPos(&CursorPos);
	ScreenToClient(UEngineAPICore::GetCore()->GetMainWindow().GetWindowHandle(), &CursorPos);

	FVector2D TileCursorPos = FVector2D(CursorPos.x / TileSizeX * TileSizeX + TileSizeX / 2, CursorPos.y / TileSizeY * TileSizeY + TileSizeY / 2);
	CursorImage->SetComponentLocation(TileCursorPos);

	if (KEY_PRESS(VK_LBUTTON) == true)
	{
		FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
		if (CursorPos.x < 0 || CursorPos.y < 0 || CursorPos.x >= WindowSize.X || CursorPos.y >= WindowSize.Y)
			return;

		int XTileIndex = CursorPos.x / TileSizeX;
		int YTileIndex = CursorPos.y / TileSizeY;

		Tiles[YTileIndex][XTileIndex]->SetSprite("Tiles", 5);
		Tiles[YTileIndex][XTileIndex]->SetName("Tile");

		for (int y = YTileIndex - 2, a = 0; y <= YTileIndex + 2; ++y, ++a)
		{
			for (int x = XTileIndex - 2, b = 0; x <= XTileIndex + 2; ++x, ++b)
			{
				if (IsTile(x, y) == true)
					CheckTiles[a][b] = true;
				else
					CheckTiles[a][b] = false;
			}
		}

		// 주변 3X3 타일을 조사한다.
		for (int y = YTileIndex - 1, a = 1; y <= YTileIndex + 1; ++y, ++a)
		{
			for (int x = XTileIndex - 1, b = 1; x <= XTileIndex + 1; ++x, ++b)
			{
				// TODO. 9개의 타일을 변경하는 함수
				if (IsTile(x, y))
					AroundTileCheckSwap(x, y, a, b);
			}
		}


	}
}

bool ATileMapEditorMode::IsTile(int _x, int _y)
{
	if (_x < 0 || _y < 0 || _x >= TileCountX || _y >= TileCountY)
		return true;
	else if (Tiles[_y][_x]->GetName() == string("Tile"))
		return true;

	return false;
}

void ATileMapEditorMode::AroundTileCheckSwap(int _X, int _Y, int _CA, int _CB)
{

}