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

	World = GetWorld()->SpawnActor<AWorld>();

	// Ŀ�� ��������Ʈ
	USpriteRenderer* NewSelectSprite = CreateDefaultSubObject<USpriteRenderer>();
	NewSelectSprite->SetSprite("CollisionTiles::28 Type05 Red", 45);
	NewSelectSprite->SetComponentScale(EGameConst::TileScale);
	NewSelectSprite->SetOrder(1);
	CurSelectSprite = NewSelectSprite;

	// ���ҽ� ����Ʈ �����
	const auto& SpritesList = UImageManager::GetInst().ViewSprites();

	string SearchName0 = UEngineString::ToUpper("BackGroundTiles::");
	string SearchName1 = UEngineString::ToUpper("CollisionTiles::");
	string SearchName2 = UEngineString::ToUpper("SpikeTiles::");
	string SearchName3 = UEngineString::ToUpper("BackGrounds::");

	for (auto& Sprite : SpritesList)
	{
		if (std::string::npos != Sprite.first.find(SearchName0))
			AddBackGroundTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(SearchName1))
			AddTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(SearchName2))
			AddSpikeTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(SearchName3))
			AddBackGroundList(Sprite.first);
	}
}

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	// ������ ǥ��
	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));

	// ���콺 ��ġ ����
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	// Ÿ�� ũ��� ������
	FIntPoint TileSize = World->GetRoom()->TileScale;
	FIntPoint TileCount = World->GetRoom()->TileCount;

	// ���콺 Ÿ�� ���� ǥ��
	FIntPoint TileCursorPos = FIntPoint(CursorPos.X - (CursorPos.X % TileSize.X) + TileSize.X / 2, CursorPos.Y - (CursorPos.Y % TileSize.Y) + TileSize.Y / 2);
	CurSelectSprite->SetComponentLocation(FVector2D(TileCursorPos.fX(), TileCursorPos.fY()));

	if (KEY_PRESS(VK_LBUTTON))
	{
		FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
		if (CursorPos.X < 0 || CursorPos.Y < 0 || CursorPos.X >= WindowSize.X || CursorPos.Y >= WindowSize.Y)
			return;

		int XTileIndex = CursorPos.X / TileSize.X;
		int YTileIndex = CursorPos.Y / TileSize.Y;

		World->GetRoom()->BackGroundTiles[YTileIndex][XTileIndex]->SetSprite(CurSelectSprite->GetCurSpriteName(), CurSelectSprite->GetCurIndex());

		// �ֺ� 3X3 Ÿ���� �����Ѵ�.
		if (CurSelectSprite->GetCurIndex() == 45)
		{
			// World->GetRoom()->BackGroundTiles[YTileIndex][XTileIndex]->SetSprite(CurSelectSprite->GetCurSpriteName(), AroundTileChange(XTileIndex, YTileIndex));

			for (int y = YTileIndex - 1; y <= YTileIndex + 1; ++y)
			{
				for (int x = XTileIndex - 1; x <= XTileIndex + 1; ++x)
				{
					if (IsSameTileName(x, y))
					{
						if (x < 0 || y < 0 || x >= TileCount.X || y >= TileCount.Y)
							continue;
						World->GetRoom()->BackGroundTiles[y][x]->SetSprite(CurSelectSprite->GetCurSpriteName(), AroundTileChange(x, y));
					}
				}
			}
		}
	}

	if (KEY_DOWN('1'))
		NextTileList();

	if (KEY_DOWN('Q'))
		PrevTileSet();

	if (KEY_DOWN('W'))
		NextTileSet();

	if (KEY_DOWN('A'))
		PrevTile();

	if (KEY_DOWN('S'))
		NextTile();

	if (KEY_DOWN('Z'))
		ShowTiles();

	if (KEY_DOWN('X'))
		ShowBackGroundTiles();
}

int ATileMapEditorMode::AroundTileChange(int _X, int _Y)
{
	uint8_t Bools = 0;

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (IsSameTileName(_X + x, _Y + y) == true)
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

	return FindAroundTile(Bools);
}

int ATileMapEditorMode::FindAroundTile(uint8_t _Bit) const
{
	int Result = -1;

	switch (_Bit)
	{
	case 0b0000'0000: // ���� ����
		Result = 39;
		break;

	case 0b0000'0010: // ���ʸ�
		Result = 27;
		break;
	case 0b0000'1000: // ���ʸ�
		Result = 38;
		break;
	case 0b0001'0000: // �����ʸ�
		Result = 36;
		break;
	case 0b0100'0000: // �Ʒ��ʸ�
		Result = 3;
		break;

	case 0b0100'0010: // ���� �Ʒ��ʸ�
		Result = 15;
		break;
	case 0b0001'1000: // ���� �����ʸ�
		Result = 37;
		break;

	case 0b0000'1011: // ���� ���� + ����
		Result = 26;
		break;
	case 0b0000'1010:
		Result = 17;
		break;
	case 0b0001'0110: // ���� ������ + ����
		Result = 24;
		break;
	case 0b0001'0010:
		Result = 16;
		break;
	case 0b0110'1000: // �Ʒ��� ���� + ����
		Result = 2;
		break;
	case 0b0100'1000:
		Result = 5;
		break;
	case 0b1101'0000: // �Ʒ��� ������ + ����
		Result = 0;
		break;
	case 0b0101'0000:
		Result = 4;
		break;

	case 0b0001'1011: // ���� ���� ������ + ����
		Result = 21;
		break;
	case 0b0001'1110:
		Result = 19;
		break;
	case 0b0001'1111:
		Result = 25;
		break;
	case 0b0001'1010:
		Result = 23;
		break;
	case 0b0100'1011: // ���� ���� �Ʒ��� + ����
		Result = 7;
		break;
	case 0b0110'1010:
		Result = 9;
		break;
	case 0b0110'1011:
		Result = 14;
		break;
	case 0b0100'1010:
		Result = 11;
		break;
	case 0b0101'0110: // ���� ������ �Ʒ��� + ����
		Result = 20;
		break;
	case 0b1101'0010:
		Result = 18;
		break;
	case 0b1101'0110:
		Result = 12;
		break;
	case 0b0101'0010:
		Result = 22;
		break;
	case 0b1101'1000: // ���� ������ �Ʒ��� + ����
		Result = 8;
		break;
	case 0b0111'1000:
		Result = 6;
		break;
	case 0b1111'1000:
		Result = 1;
		break;
	case 0b0101'1000:
		Result = 10;
		break;

	case 0b0101'1011:  // �� ���� + ���� ����
		Result = 34;
		break;
	case 0b0101'1110:
		Result = 35;
		break;
	case 0b0111'1010:
		Result = 46;
		break;
	case 0b1101'1010:
		Result = 47;
		break;

	case 0b0101'1111:
		Result = 31;
		break;
	case 0b0111'1011:
		Result = 30;
		break;
	case 0b1101'1011:
		Result = 33;
		break;
	case 0b0111'1110:
		Result = 32;
		break;
	case 0b1101'1110:
		Result = 43;
		break;
	case 0b1111'1010:
		Result = 42;
		break;

	case 0b1111'1110:
		Result = 41;
		break;
	case 0b1111'1011:
		Result = 40;
		break;
	case 0b1101'1111:
		Result = 29;
		break;
	case 0b0111'1111:
		Result = 28;
		break;

	case 0b0101'1010:
		Result = 44;
		break;

	case 0b1111'1111:
		Result = 13;
		break;
	}

	if (Result == -1)
		MSGASSERT(nullptr, "Ÿ�� �˰����� �̻��մϴ�.");

	return Result;
}

bool ATileMapEditorMode::IsSameTileName(int _x, int _y) const
{
	if (_x < 0 || _y < 0 || _x >= World->GetRoom()->TileCount.X || _y >= World->GetRoom()->TileCount.Y)
		return true;
	else if (World->GetRoom()->BackGroundTiles[_y][_x]->GetCurSpriteName() == CurSelectSprite->GetCurSpriteName())
		return true;

	return false;
}

void ATileMapEditorMode::NextTileList()
{
	// TODO. ���� �ؾߵ�
	if (CurSelectTileList == &BackGroundTileList)
	{
		CurSelectTileList = &TileList;
	}
	else if (CurSelectTileList == &TileList)
	{
		CurSelectTileList = &SpikeTileList;
	}
	else if (CurSelectTileList == &SpikeTileList)
	{
		CurSelectTileList = &BackGroundTileList;
	}
}

void ATileMapEditorMode::PrevTileSet()
{
	--CurTileSetIndex;
	if (CurTileSetIndex < 0)
		CurTileSetIndex = CurSelectTileList->size() - size_t(1);

	int Curindex = CurSelectSprite->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite((*CurSelectTileList)[CurTileSetIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectSprite->SetSprite((*CurSelectTileList)[CurTileSetIndex], Curindex);
}

void ATileMapEditorMode::NextTileSet()
{
	++CurTileSetIndex;
	if (CurTileSetIndex >= CurSelectTileList->size())
		CurTileSetIndex = 0;

	int Curindex = CurSelectSprite->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite((*CurSelectTileList)[CurTileSetIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectSprite->SetSprite((*CurSelectTileList)[CurTileSetIndex], Curindex);
}

void ATileMapEditorMode::PrevTile()
{
	int index = CurSelectSprite->GetCurIndex();
	--index;
	if (index < 0)
		index = CurSelectSprite->GetMaxIndex() - 1;
	CurSelectSprite->SetSprite(CurSelectSprite->GetCurSpriteName(), index);
}

void ATileMapEditorMode::NextTile()
{
	int index = CurSelectSprite->GetCurIndex();
	++index;
	if (index >= CurSelectSprite->GetMaxIndex())
		index = 0;
	CurSelectSprite->SetSprite(CurSelectSprite->GetCurSpriteName(), index);
}

void ATileMapEditorMode::ShowTiles()
{
	auto& room = World->GetRoom()->Tiles;
	for (size_t y = 0; y < room.size(); ++y)
	{
		for (size_t x = 0; x < room[y].size(); ++x)
		{
			room[y][x]->SetActive(!room[y][x]->IsActive());
		}
	}
}

void ATileMapEditorMode::ShowBackGroundTiles()
{
	auto& room = World->GetRoom()->BackGroundTiles;
	for (size_t y = 0; y < room.size(); ++y)
	{
		for (size_t x = 0; x < room[y].size(); ++x)
		{
			room[y][x]->SetActive(!room[y][x]->IsActive());
		}
	}
}

void ATileMapEditorMode::PrevBackGroundImage()
{
	--CurBackGroundIndex;
	if (CurBackGroundIndex < 0)
	{
		++CurBackGroundIndex;
		return;
	}
	World->GetRoom()->BackGround->SetBackGround(BackGroundList[CurBackGroundIndex]);
}

void ATileMapEditorMode::NextBackGroundImage()
{
	++CurBackGroundIndex;
	if (CurBackGroundIndex >= BackGroundList.size())
	{
		--CurBackGroundIndex;
		return;
	}
	World->GetRoom()->BackGround->SetBackGround(BackGroundList[CurBackGroundIndex]);
}
