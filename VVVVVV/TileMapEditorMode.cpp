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

		// �ֺ� 3X3 Ÿ���� �����Ѵ�.
		for (int y = YTileIndex - 1; y <= YTileIndex + 1; ++y)
		{
			for (int x = XTileIndex - 1; x <= XTileIndex + 1; ++x)
			{
				// TODO. 9���� Ÿ���� �����ϴ� �Լ�
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

	if ((Bools & 1 << 1)) // ���� �ִ�
	{
		if ((Bools & 1 << 3) == false) // ���� �ִ�
		{
			Bools &= ~(1 << 0);
		}
		if ((Bools & 1 << 4) == false) // ������ �ִ�
		{
			Bools &= ~(1 << 2);
		}
	}
	else
	{
		Bools &= ~(1 << 0);
		Bools &= ~(1 << 2);
	}

	if ((Bools & 1 << 6)) // �Ʒ��� �ִ�
	{
		if ((Bools & 1 << 3) == false) // ���� �ִ�
		{
			Bools &= ~(1 << 5);
		}
		if ((Bools & 1 << 4) == false) // ������ �ִ�
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
	int Result = -1;

	switch (_Bit)
	{
	case 0b0000'0000: // ���� ����
		Result = 21;
		break;

	case 0b0000'0010: // ���ʸ�
		Result = 15;
		break;
	case 0b0000'1000: // ���ʸ�
		Result = 20;
		break;
	case 0b0001'0000: // �����ʸ�
		Result = 18;
		break;
	case 0b0100'0000: // �Ʒ��ʸ�
		Result = 3;
		break;

	case 0b0100'0010: // ���� �Ʒ��ʸ�
		Result = 9;
		break;
	case 0b0001'1000: // ���� �����ʸ�
		Result = 19;
		break;

	case 0b0000'1011:
	case 0b0000'1010: // ���� ���� + ����
		Result = 14;
		break;
	case 0b0001'0110:
	case 0b0001'0010: // ���� ������ + ����
		Result = 12;
		break;
	case 0b0110'1000:
	case 0b0100'1000: // �Ʒ��� ���� + ����
		Result = 2;
		break;
	case 0b1101'0000:
	case 0b0101'0000: // �Ʒ��� ������ + ����
		Result = 0;
		break;

	case 0b0001'1011:
	case 0b0001'1110:
	case 0b0001'1111:
	case 0b0001'1010: // ���� ���� ������ + ����
		Result = 13;
		break;
	case 0b0100'1011:
	case 0b0110'1010:
	case 0b0110'1011:
	case 0b0100'1010: // ���� ���� �Ʒ��� + ����
		Result = 8;
		break;
	case 0b0101'0110:
	case 0b1101'0010:
	case 0b1101'0110:
	case 0b0101'0010: // ���� ������ �Ʒ��� + ����
		Result = 6;
		break;
	case 0b1101'1000:
	case 0b0111'1000:
	case 0b1111'1000:
	case 0b0101'1000: // ���� ������ �Ʒ��� + ����
		Result = 1;
		break;

		// ���ҽ� �̹��� ����, ��ü �̹���
	case 0b0101'1011:
	case 0b0101'1110:
	case 0b0111'1010:
	case 0b1101'1010:
		Result = 7;
		break;

		// ���ҽ� �̹��� ����, ��ü �̹���
	case 0b0101'1111:
	case 0b0111'1011:
	case 0b1101'1011:
	case 0b0111'1110:
	case 0b1101'1110:
	case 0b1111'1010:
		Result = 7;
		break;

	case 0b1111'1110:
		Result = 23;
		break;
	case 0b1111'1011:
		Result = 22;
		break;
	case 0b1101'1111:
		Result = 17;
		break;
	case 0b0111'1111:
		Result = 16;
		break;

	case 0b1111'1111:

	case 0b0101'1010: // �� ���� + ���� ����
		Result = 7;
		break;
	}

	if (Result == -1)
		MSGASSERT(nullptr, "Ÿ�� �˰������� �̻��մϴ�.");

	return Result;
}