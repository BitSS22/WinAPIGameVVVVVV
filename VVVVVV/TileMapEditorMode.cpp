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

		// 주변 3X3 타일을 조사한다.
		for (int y = YTileIndex - 1; y <= YTileIndex + 1; ++y)
		{
			for (int x = XTileIndex - 1; x <= XTileIndex + 1; ++x)
			{
				// TODO. 타일을 검사해서 변경한다.
				if (IsTile(x, y) == true)
					AroundTileCheckSwap(x, y);
			}
		}


	}
}

bool ATileMapEditorMode::IsTile(int _x, int _y)
{
	if (_x < 0 || _y < 0 || _x >= TileCountX || _y >= TileCountY)
		return true;
	else if (Tiles[_y][_x]->GetName() == string("NoneTile"))
		return false;

	return true;
}

void ATileMapEditorMode::AroundTileCheckSwap(int _XIndex, int _YIndex)
{
	vector<vector<bool>> Result = {};

	Result.resize(3);

	for (int y = _YIndex - 1; y <= _YIndex + 1; ++y)
	{
		Result[y].resize(3);
		for (int x = _XIndex - 1; x <= _XIndex + 1; ++x)
		{
			if (IsTile(x, y) == true)
				Result[y][x] = true;
			else
				Result[y][x] = false;
		}
	}
	//TODO.
	return;
}

void SwapTile(USpriteRenderer& _Tile)
{

}