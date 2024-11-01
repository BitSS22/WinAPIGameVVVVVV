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
	NewSprite->SetSprite("Tiles", 7);
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

		// 주변 3X3 타일을 조사한다.
		for (int y = YTileIndex - 1; y <= YTileIndex + 1; ++y)
		{
			for (int x = XTileIndex - 1; x <= XTileIndex + 1; ++x)
			{
				// TODO. 9개의 타일을 변경하는 함수
				if (IsTile(x, y))
				{
					if (x < 0 || y < 0 || x >= TileCountX || y >= TileCountY)
						continue;
					USpriteRenderer* CurTile = Tiles[y][x];
					CurTile->SetSprite("Tiles", AroundTileCheckSwap(x, y));
				}
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

int ATileMapEditorMode::AroundTileCheckSwap(int _X, int _Y)
{
	uint8_t Bools = 0;

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (IsTile(_X + x, _Y + y) == true)
			{
				if (x == 0 && y == 0)
					continue;

				int Shift = (y + 1) * 3 + (x + 1);
				if (Shift >= 4)
					--Shift;

				Bools |= 1 << Shift;
			}
		}
	}

	if ((Bools & 1 << 1)) // 위쪽 있니
	{
		if ((Bools & 1 << 3) == false) // 왼쪽 있니
		{
			Bools &= ~(1 << 0);
		}
		if ((Bools & 1 << 4) == false) // 오른쪽 있니
		{
			Bools &= ~(1 << 2);
		}
	}
	else
	{
		Bools &= ~(1 << 0);
		Bools &= ~(1 << 2);
	}

	if ((Bools & 1 << 6)) // 아래쪽 있니
	{
		if ((Bools & 1 << 3) == false) // 왼쪽 있니
		{
			Bools &= ~(1 << 5);
		}
		if ((Bools & 1 << 4) == false) // 오른쪽 있니
		{
			Bools &= ~(1 << 7);
		}
	}
	else
	{
		Bools &= ~(1 << 5);
		Bools &= ~(1 << 7);
	}

	return FindIndex(Bools);
}

int ATileMapEditorMode::FindIndex(uint8_t _Bit)
{
	int Result = 7;

	switch (_Bit)
	{
	case 0b0000'0000: // 인접 없음
		Result = 7;
		break;

	case 0b0000'0010: // 위쪽만
		Result = 15;
		break;
	case 0b0000'1000: // 왼쪽만
		Result = 20;
		break;
	case 0b0001'0000: // 오른쪽만
		Result = 18;
		break;
	case 0b0100'0000: // 아래쪽만
		Result = 3;
		break;

	case 0b0100'0010: // 위쪽 아래쪽만
		Result = 9;
		break;
	case 0b0001'1000: // 왼쪽 오른쪽만
		Result = 19;
		break;

	case 0b0000'1011:
	case 0b0000'1010: // 위쪽 왼쪽 + 사이
		Result = 14;
		break;
	case 0b0001'0110:
	case 0b0001'0010: // 위쪽 오른쪽 + 사이
		Result = 12;
		break;
	case 0b0110'1000:
	case 0b0100'1000: // 아래쪽 왼쪽 + 사이
		Result = 2;
		break;
	case 0b1101'0000:
	case 0b0101'0000: // 아래쪽 오른쪽 + 사이
		Result = 0;
		break;
	}



	return Result;
}
