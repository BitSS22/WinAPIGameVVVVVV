#include "pch.h"
#include "TileMapEditorMode.h"
#include "Player.h"
#include "MoveEntity.h"
#include "Entity.h"
#include "World.h"

ATileMapEditorMode::ATileMapEditorMode()
{
}

ATileMapEditorMode::~ATileMapEditorMode()
{
}

void ATileMapEditorMode::BeginPlay()
{
	Super::BeginPlay();

	LoadResourceList();

	World = GetWorld()->SpawnActor<AWorld>();

	// Ŀ�� ��������Ʈ
	CurSelectSprite = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectSprite->SetSprite("CollisionTiles::Type00-1 Cyan", 44);
	CurSelectSprite->SetComponentScale(EGameConst::TileScale);
	CurSelectSprite->SetOrder(ERenderOrder::EDITOR_CURSOR);

	CurSelectEntityType = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectEntityType->SetSprite("Enemies::001 Stop Cyan", 0);
	FVector2D SpriteSize = UImageManager::GetInst().FindSprite("Enemies::001 Stop Cyan")->GetSpriteData(0).Transform.Scale;
	CurSelectEntityType->SetComponentScale(SpriteSize);
	CurSelectEntityType->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	CurSelectEntityType->SetOrder(ERenderOrder::EDITOR_CURSOR);
	CurSelectEntityType->SetActive(false);
	

	// Set Debug
	UEngineDebug::SetIsDebug(true);
}

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	// ������ ǥ��
	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));

	EditorKeyCheck();

	DebugText();
}

int ATileMapEditorMode::AroundTileChange(const string& _Name, int _X, int _Y)
{
	uint8_t Bools = 0;

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (IsSameTileName(_Name, _X + x, _Y + y) == true)
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

bool ATileMapEditorMode::IsSameTileName(const string& _Name, int _x, int _y) const
{
	auto& CurSelectTileMap = GetCurSelectTileMap();

	if (_x < 0 || _y < 0 || _x >= World->GetRoom()->TileCount.X || _y >= World->GetRoom()->TileCount.Y)
		return true;
	else if (CurSelectTileMap[_y][_x]->GetCurSpriteName() == _Name)
		return true;

	return false;
}

void ATileMapEditorMode::ChangeTile(bool _AroundTileChange, FIntPoint _Index)
{
	auto& CurSelectTileMap = GetCurSelectTileMap();

	FIntPoint TileCount = World->GetRoom()->TileCount;

	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	if (CursorPos.X < 0 || CursorPos.Y < 0 || CursorPos.X >= WindowSize.X || CursorPos.Y >= WindowSize.Y)
		return;

	int MaxIndex = CurSelectSprite->GetMaxIndex();

	CurSelectTileMap[_Index.Y][_Index.X]->SetSprite(CurSelectSprite->GetCurSpriteName(), CurSelectSprite->GetCurIndex());
	CurSelectTileMap[_Index.Y][_Index.X]->ChangeAnimation(CurSelectSprite->GetCurSpriteName(), false);

	// Auto Tile�� �ֺ� 3X3 Ÿ���� �����Ѵ�.
	if ((_AroundTileChange || CurSelectSprite->GetCurIndex() == 45) && MaxIndex >= 47)
	{
		for (int y = _Index.Y - 1; y <= _Index.Y + 1; ++y)
		{
			for (int x = _Index.X - 1; x <= _Index.X + 1; ++x)
			{
				if (IsSameTileName(CurSelectSprite->GetCurSpriteName(), x, y))
				{
					if (x < 0 || y < 0 || x >= TileCount.X || y >= TileCount.Y)
						continue;
					CurSelectTileMap[y][x]->SetSprite(CurSelectSprite->GetCurSpriteName(), AroundTileChange(CurSelectSprite->GetCurSpriteName(), x, y));
				}
			}
		}
	}
}

void ATileMapEditorMode::DeleteTile(bool _AroundTileChange, FIntPoint _Index)
{
	auto& CurSelectTileMap = GetCurSelectTileMap();

	FIntPoint TileCount = World->GetRoom()->TileCount;

	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	if (CursorPos.X < 0 || CursorPos.Y < 0 || CursorPos.X >= WindowSize.X || CursorPos.Y >= WindowSize.Y)
		return;

	string PrevName = CurSelectTileMap[_Index.Y][_Index.X]->GetCurSpriteName();
	int MaxIndex = CurSelectTileMap[_Index.Y][_Index.X]->GetMaxIndex();

	CurSelectTileMap[_Index.Y][_Index.X]->SetSprite("None Tile", 0);

	// Auto Tile�� �ֺ� 3X3 Ÿ���� �����Ѵ�.
	if ((_AroundTileChange || CurSelectSprite->GetCurIndex() == 45) && MaxIndex >= 47)
	{
		for (int y = _Index.Y - 1; y <= _Index.Y + 1; ++y)
		{
			for (int x = _Index.X - 1; x <= _Index .X + 1; ++x)
			{
				if (IsSameTileName(PrevName, x, y))
				{
					if (x < 0 || y < 0 || x >= TileCount.X || y >= TileCount.Y)
						continue;
					CurSelectTileMap[y][x]->SetSprite(PrevName, AroundTileChange(PrevName, x, y));
				}
			}
		}
	}
}

void ATileMapEditorMode::MoveRoom(FIntPoint _Index)
{
	CurAdjustmentEntity = nullptr;
	CurAdjustmentEntityIndex = -1;

	World->MoveRoom(_Index);
}

void ATileMapEditorMode::SwitchLoopRoom()
{
	FIntPoint Index = World->CurRoomIndex;
	bool& IsLoop = World->RoomDatas[Index.Y][Index.X].LoopRoom;
	IsLoop = !IsLoop;
}

void ATileMapEditorMode::NextTileList()
{
	++CurSelectTileList;
	CurSelectSprite->SetSprite(TileLists[static_cast<int>(CurSelectTileList)][0], 0);
	CurTileSetIndex = 0;
}

void ATileMapEditorMode::PrevTileList()
{
	--CurSelectTileList;
	CurSelectSprite->SetSprite(TileLists[static_cast<int>(CurSelectTileList)][0], 0);
	CurTileSetIndex = 0;
}

void ATileMapEditorMode::PrevTileSet()
{
	--CurTileSetIndex;
	if (CurTileSetIndex < 0 || CurTileSetIndex >= TileLists[static_cast<int>(CurSelectTileList)].size())
		CurTileSetIndex = static_cast<int>(TileLists[static_cast<int>(CurSelectTileList)].size()) - 1;

	int Curindex = CurSelectSprite->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(TileLists[static_cast<int>(CurSelectTileList)][CurTileSetIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectSprite->SetSprite(TileLists[static_cast<int>(CurSelectTileList)][CurTileSetIndex], Curindex);
}

void ATileMapEditorMode::NextTileSet()
{
	++CurTileSetIndex;
	if (CurTileSetIndex < 0 || CurTileSetIndex >= TileLists[static_cast<int>(CurSelectTileList)].size())
		CurTileSetIndex = 0;

	int Curindex = CurSelectSprite->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(TileLists[static_cast<int>(CurSelectTileList)][CurTileSetIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectSprite->SetSprite(TileLists[static_cast<int>(CurSelectTileList)][CurTileSetIndex], Curindex);
}

void ATileMapEditorMode::PrevTile()
{
	int index = CurSelectSprite->GetCurIndex();
	--index;
	if (index < 0 || index >= CurSelectSprite->GetMaxIndex())
		index = CurSelectSprite->GetMaxIndex() - 1;
	CurSelectSprite->SetSprite(CurSelectSprite->GetCurSpriteName(), index);
}

void ATileMapEditorMode::NextTile()
{
	int index = CurSelectSprite->GetCurIndex();
	++index;
	if (index < 0 || index >= CurSelectSprite->GetMaxIndex())
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

void ATileMapEditorMode::PickUpTile()
{
	FIntPoint TileIndex = World->GetRoom()->GetOnTileIndex(UEngineAPICore::GetCore()->GetMainWindow().GetMousePos());
	if (TileIndex.X < 0 || TileIndex.X >= World->GetRoom()->TileCount.X || TileIndex.Y < 0 || TileIndex.Y >= World->GetRoom()->TileCount.Y)
		return;
	auto& SelectTileMap = GetCurSelectTileMap();
	CurSelectSprite->SetSprite(SelectTileMap[TileIndex.Y][TileIndex.X]->GetCurSpriteName(), SelectTileMap[TileIndex.Y][TileIndex.X]->GetCurIndex());
}

void ATileMapEditorMode::LoadResourceList()
{
	// ���ҽ� ����Ʈ �����
	const auto& SpritesList = UImageManager::GetInst().ViewSprites();

	string BackGroundTiles = UEngineString::ToUpper("BackGroundTiles::");
	string CollisionTiles = UEngineString::ToUpper("CollisionTiles::");
	string SpikeTiles = UEngineString::ToUpper("SpikeTiles::");
	string AnimationTiles = UEngineString::ToUpper("AnimationTiles::");
	string RailTiles = UEngineString::ToUpper("RailTiles::");

	string BackGrounds = UEngineString::ToUpper("BackGrounds::");

	string Platforms = UEngineString::ToUpper("Platforms::");
	string InterObjects = UEngineString::ToUpper("InterObjects::");
	string Enemies = UEngineString::ToUpper("Enemies::");

	for (auto& Sprite : SpritesList)
	{
		if (std::string::npos != Sprite.first.find(BackGroundTiles))
			AddBackGroundTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(CollisionTiles))
			AddTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(SpikeTiles))
			AddSpikeTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(AnimationTiles))
			AddAnimationTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(RailTiles))
			AddAnimationTileList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(BackGrounds))
			AddBackGroundList(Sprite.first);

		else if (std::string::npos != Sprite.first.find(Platforms))
			AddPlatformList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(InterObjects))
			AddInterObjectList(Sprite.first);
		else if (std::string::npos != Sprite.first.find(Enemies))
			AddEnermyList(Sprite.first);
	}
}

void ATileMapEditorMode::EditorKeyCheck()
{
	// ���콺 ��ġ ����
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	// Ÿ�� ũ��� ������
	FIntPoint TileSize = World->GetRoom()->TileScale;
	FIntPoint TileCount = World->GetRoom()->TileCount;

	// ���콺 Ÿ�� ���� ǥ��
	FIntPoint TileCursorPos = FIntPoint(CursorPos.X - (CursorPos.X % TileSize.X) + TileSize.X / 2, CursorPos.Y - (CursorPos.Y % TileSize.Y) + TileSize.Y / 2);
	CurSelectSprite->SetComponentLocation(FVector2D(TileCursorPos.fX(), TileCursorPos.fY()));

	FIntPoint CurTileIndex = CursorPos / TileSize;

	if (KEY_DOWN(VK_ESCAPE))
		UEngineDebug::SwitchIsDebug();

	if (KEY_PRESS(VK_LBUTTON))
	{
		bool Around = false;
		if (KEY_PRESS(VK_CONTROL))
			Around = true;

		if (KEY_PRESS(VK_SHIFT))
		{
			for (int y = CurTileIndex.Y - 1; y <= CurTileIndex.Y + 1; ++y)
			{
				for (int x = CurTileIndex.X - 1; x <= CurTileIndex.X + 1; ++x)
				{
					if (x < 0 || y < 0 || x >= TileCount.X || y >= TileCount.Y)
						continue;
					ChangeTile(Around, FIntPoint(x, y));
				}
			}
		}
		else
			ChangeTile(Around, CurTileIndex);
	}

	if (KEY_PRESS(VK_RBUTTON))
	{
		bool Around = false;
		if (KEY_PRESS(VK_CONTROL))
			Around = true;

		if (KEY_PRESS(VK_SHIFT))
		{
			for (int y = CurTileIndex.Y - 1; y <= CurTileIndex.Y + 1; ++y)
			{
				for (int x = CurTileIndex.X - 1; x <= CurTileIndex.X + 1; ++x)
				{
					if (x < 0 || y < 0 || x >= TileCount.X || y >= TileCount.Y)
						continue;
					DeleteTile(Around, FIntPoint(x, y));
				}
			}
		}
		else
			DeleteTile(Around, CurTileIndex);
	}

	// Tile ����

	if (KEY_DOWN(VK_XBUTTON1))
		PickUpTile();
	if (KEY_DOWN(VK_XBUTTON2))
		NextTileList();

	if (KEY_DOWN('1'))
		PrevTileSet();
	if (KEY_DOWN('2'))
		NextTileSet();

	if (KEY_DOWN('Q'))
		PrevTile();
	if (KEY_DOWN('E'))
		NextTile();

	if (KEY_DOWN(VK_F1))
		ShowBackGroundTiles();
	if (KEY_DOWN(VK_F2))
		ShowTiles();

	// ���ȭ��
	if (KEY_DOWN('O'))
		PrevBackGroundImage();
	if (KEY_DOWN('P'))
		NextBackGroundImage();

	// �� �̵�, ���̺�
	FIntPoint RoomIndex = World->CurRoomIndex;
	if (KEY_DOWN('W'))
	{
		RoomIndex.Y -= 1;
		MoveRoom(RoomIndex);
	}
	if (KEY_DOWN('S'))
	{
		RoomIndex.Y += 1;
		MoveRoom(RoomIndex);
	}
	if (KEY_DOWN('A'))
	{
		RoomIndex.X -= 1;
		MoveRoom(RoomIndex);
	}
	if (KEY_DOWN('D'))
	{
		RoomIndex.X += 1;
		MoveRoom(RoomIndex);
	}
	if (KEY_DOWN('R'))
		MoveRoom(RoomIndex);

	// Entity ����
	if (KEY_DOWN(VK_RETURN))
		CreateEntity();
	if (KEY_DOWN(VK_DELETE))
		DeleteEntity();

	FVector2D Dir = FVector2D::ZERO;

	if (KEY_DOWN(VK_UP))
		Dir += FVector2D::UP;
	if (KEY_DOWN(VK_DOWN))
		Dir += FVector2D::DOWN;
	if (KEY_DOWN(VK_LEFT))
		Dir += FVector2D::LEFT;
	if (KEY_DOWN(VK_RIGHT))
		Dir += FVector2D::RIGHT;

	if (KEY_PRESS(VK_SHIFT))
		Dir = Dir * 8;
	else if (KEY_PRESS(VK_CONTROL))
		Dir = Dir * 64;

	if (Dir != FVector2D::ZERO)
		AddEntityLocation(Dir);


	if (KEY_DOWN(VK_OEM_MINUS))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntitySpeed(-8.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntitySpeed(-64.f);
		else
			AddEntitySpeed(-1.f);
	}
	if (KEY_DOWN(VK_OEM_PLUS))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntitySpeed(8.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntitySpeed(64.f);
		else
			AddEntitySpeed(1.f);
	}

	if (KEY_DOWN(VK_OEM_4))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveLenght(-8.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveLenght(-64.f);
		else
			AddEntityMoveLenght(-1.f);
	}
	if (KEY_DOWN(VK_OEM_6))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveLenght(8.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveLenght(64.f);
		else
			AddEntityMoveLenght(1.f);
	}

	if (KEY_DOWN('9'))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveOffSet(-8.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveOffSet(-64.f);
		else
			AddEntityMoveOffSet(-1.f);
	}
	if (KEY_DOWN('0'))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveOffSet(8.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveOffSet(64.f);
		else
			AddEntityMoveOffSet(1.f);
	}

	if (KEY_DOWN('N'))
		PrevSelectEntity();
	if (KEY_DOWN('M'))
		NextSelectEntity();

	if (KEY_DOWN('3'))
		PrevEntityList();
	if (KEY_DOWN('4'))
		NextEntityList();

	if (KEY_DOWN('Z'))
	{
		if (KEY_PRESS(VK_CONTROL))
			PrevEntityType(7);
		else
			PrevEntityType(1);
	}
	if (KEY_DOWN('C'))
	{
		if (KEY_PRESS(VK_CONTROL))
			NextEntityType(7);
		else
			NextEntityType(1);
	}

	Dir = FVector2D::ZERO;
	if (KEY_DOWN('U'))
		Dir += FVector2D::UP;
	else if (KEY_DOWN('J'))
		Dir += FVector2D::DOWN;
	else if (KEY_DOWN('H'))
		Dir += FVector2D::LEFT;
	else if (KEY_DOWN('K'))
		Dir += FVector2D::RIGHT;

	if (Dir != FVector2D::ZERO)
	{
		if (KEY_PRESS(VK_CONTROL))
			SetEntityDir(Dir);
		else
			AddEntityDir(Dir);
	}

	if (KEY_DOWN(VK_F3))
		World->SaveFile();

	if (KEY_DOWN(VK_F4))
		World->LoadFile();

	if (KEY_DOWN(VK_TAB))
		SwitchLoopRoom();
}

void ATileMapEditorMode::DebugText()
{
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FIntPoint RoomIndex = World->CurRoomIndex;

	// DEBUG TEXT
	string CurTileList = {};

	string str = "Selected Entity : ";
	str += CurSelectEntityType->GetCurSpriteName();
	UEngineDebug::CoreOutputString(str);

	str = "World Index : ";
	str += std::to_string(RoomIndex.X);
	str += ",";
	str += std::to_string(RoomIndex.Y);
	str += ", RoomLoop : ";
	if (World->RoomDatas[World->CurRoomIndex.Y][World->CurRoomIndex.X].LoopRoom == true)
		str += "True";
	else
		str += "False";
	UEngineDebug::CoreOutputString(str);

	str = "Tile Set Index : ";
	str += std::to_string(CurTileSetIndex);
	UEngineDebug::CoreOutputString(str);

	str = "Select Tile Name : ";
	str += CurSelectSprite->GetCurSpriteName();
	str += ", Index : ";
	str += std::to_string(CurSelectSprite->GetCurIndex());
	UEngineDebug::CoreOutputString(str);

	FIntPoint TileCursorIndex = World->GetRoom()->GetOnTileIndex(CursorPos);
	if ((TileCursorIndex.X < 0 || TileCursorIndex.X >= World->GetRoom()->TileCount.X || TileCursorIndex.Y < 0 || TileCursorIndex.Y >= World->GetRoom()->TileCount.Y) == false)
	{
		str = "On Tile Name : ";
		str += GetCurSelectTileMap()[TileCursorIndex.Y][TileCursorIndex.X]->GetCurSpriteName();
		str += ", Index : ";
		str += std::to_string(GetCurSelectTileMap()[TileCursorIndex.Y][TileCursorIndex.X]->GetCurIndex());
		UEngineDebug::CoreOutputString(str);
	}
	
	if (CurAdjustmentEntity != nullptr)
	{
		FTransform Trans = CurAdjustmentEntity->GetActorTransform();
		Trans.Scale = FVector2D(Trans.Scale.X * 2, Trans.Scale.X * 2);
		UEngineDebug::CoreDebugRender(Trans, UEngineDebug::EDebugPosType::Circle);

		str = "Selected Entity Name : ";
		str += CurAdjustmentEntity->GetRenderer()->GetCurSpriteName();
		str += ", List Number : ";
		str += std::to_string(CurAdjustmentEntityIndex);
		UEngineDebug::CoreOutputString(str);

		AMoveEntity* MoveEntity = dynamic_cast<AMoveEntity*>(CurAdjustmentEntity);
		if (MoveEntity != nullptr)
		{
			str = "Location : ";
			str += std::to_string(MoveEntity->GetEntityDefualtLocation().X);
			str += ",";
			str += std::to_string(MoveEntity->GetEntityDefualtLocation().Y);
			str += ", Scale : ";
			str += std::to_string(MoveEntity->GetActorScale().X);
			str += ",";
			str += std::to_string(MoveEntity->GetActorScale().Y);
			str += ", MoveLenght : ";
			str += std::to_string(MoveEntity->GetMoveLenght());
			UEngineDebug::CoreOutputString(str);

			str = "Speed : ";
			str += std::to_string(MoveEntity->GetSpeed());
			str += ", StartOffset : ";
			str += std::to_string(MoveEntity->GetMoveLenghtOffset());
			str += ", Direction : ";
			str += std::to_string(MoveEntity->GetEntityDefualtDir().X);
			str += ", ";
			str += std::to_string(MoveEntity->GetEntityDefualtDir().Y);
			UEngineDebug::CoreOutputString(str);
		}
		else
		{
			str = "Location : ";
			str += std::to_string(MoveEntity->GetEntityDefualtLocation().X);
			str += ",";
			str += std::to_string(MoveEntity->GetEntityDefualtLocation().Y);
			str += "Scale : ";
			str += std::to_string(MoveEntity->GetActorScale().X);
			str += ",";
			str += std::to_string(MoveEntity->GetActorScale().Y);
			UEngineDebug::CoreOutputString(str);
		}
	}
}

void ATileMapEditorMode::PrevBackGroundImage()
{
	--CurBackGroundIndex;
	if (CurBackGroundIndex < 0)
		CurBackGroundIndex = static_cast<int>(TileLists[static_cast<int>(TileList::BackGroundList)].size() - 1);

	World->GetRoom()->BackGround->SetBackGround(TileLists[static_cast<int>(TileList::BackGroundList)][CurBackGroundIndex]);
}

void ATileMapEditorMode::NextBackGroundImage()
{
	++CurBackGroundIndex;
	if (CurBackGroundIndex >= TileLists[static_cast<int>(TileList::BackGroundList)].size())
		CurBackGroundIndex = 0;

	World->GetRoom()->BackGround->SetBackGround(TileLists[static_cast<int>(TileList::BackGroundList)][CurBackGroundIndex]);
}

void ATileMapEditorMode::CreateEntity()
{
	if (CurSelectEntityList == EntityList::Enemies || CurSelectEntityList == EntityList::Platforms)
	{
		AMoveEntity* NewEntity = GetWorld()->SpawnActor<AMoveEntity>();
		NewEntity->MoveEntityDefaultSetUp(CurSelectEntityType->GetCurSpriteName(), CurSelectEntityType->GetComponentLocation(), FVector2D::RIGHT, EGameConst::DefualtSpeed, EGameConst::DefualtMoveLen, 0.f);
		World->GetRoom()->Entites.push_back(NewEntity);
		CurAdjustmentEntity = NewEntity;
		CurAdjustmentEntityIndex = static_cast<int>(World->GetRoom()->Entites.size() - 1);
	}
	else if (CurSelectEntityList == EntityList::InterObjects)
	{
		// TODO. 
	}
}

void ATileMapEditorMode::DeleteEntity()
{
	if (CurAdjustmentEntity == nullptr)
		return;

	auto& Entites = World->GetRoom()->Entites;
	CurAdjustmentEntity->Destroy();
	Entites.erase(Entites.begin() + CurAdjustmentEntityIndex);
	--CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex == -1)
		CurAdjustmentEntity = nullptr;
	else
		CurAdjustmentEntity = Entites[CurAdjustmentEntityIndex];
}

TileList& operator++(TileList& _List)
{
	int Value = static_cast<int>(_List);
	if (++Value >= static_cast<int>(TileList::LAST) - 1)
		Value = 0;
	return _List = static_cast<TileList>(Value);
}

TileList& operator--(TileList& _List)
{
	int Value = static_cast<int>(_List);
	if (--Value < 0)
		Value = static_cast<int>(TileList::LAST) - 2;
	return _List = static_cast<TileList>(Value);
}

EntityList& operator++(EntityList& _List)
{
	int Value = static_cast<int>(_List);
	if (++Value >= static_cast<int>(EntityList::LAST))
		Value = 0;
	return _List = static_cast<EntityList>(Value);
}

EntityList& operator--(EntityList& _List)
{
	int Value = static_cast<int>(_List);
	if (--Value < 0)
		Value = static_cast<int>(EntityList::LAST) - 1;
	return _List = static_cast<EntityList>(Value);
}

void ATileMapEditorMode::PrevEntityList()
{
	++CurSelectEntityList;
	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurSelectEntityList)][0], 0);
	CurEntityIndex = 0;
}

void ATileMapEditorMode::NextEntityList()
{
	--CurSelectEntityList;
	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurSelectEntityList)][0], 0);
	CurEntityIndex = 0;
}

void ATileMapEditorMode::PrevEntityType(int _AddIndex)
{
	CurEntityIndex -= _AddIndex;
	if (CurEntityIndex < 0 || CurEntityIndex >= EntityLists[static_cast<int>(CurSelectEntityList)].size())
		CurEntityIndex = static_cast<int>(EntityLists[static_cast<int>(CurSelectEntityList)].size()) - 1;

	int Curindex = CurSelectEntityType->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(EntityLists[static_cast<int>(CurSelectEntityList)][CurEntityIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurSelectEntityList)][CurEntityIndex], Curindex);
}

void ATileMapEditorMode::NextEntityType(int _AddIndex)
{
	CurEntityIndex += _AddIndex;
	if (CurEntityIndex < 0 || CurEntityIndex >= EntityLists[static_cast<int>(CurSelectEntityList)].size())
		CurEntityIndex = 0;

	int Curindex = CurSelectEntityType->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(EntityLists[static_cast<int>(CurSelectEntityList)][CurEntityIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurSelectEntityList)][CurEntityIndex], Curindex);
}

void ATileMapEditorMode::PrevSelectEntity()
{
	if (World->GetRoom()->Entites.empty() == true)
		return;

	--CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex < 0)
		CurAdjustmentEntityIndex = static_cast<int>(World->GetRoom()->Entites.size() - 1);
	
	CurAdjustmentEntity = World->GetRoom()->Entites[CurAdjustmentEntityIndex];
}

void ATileMapEditorMode::NextSelectEntity()
{
	if (World->GetRoom()->Entites.empty() == true)
		return;

	++CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex >= World->GetRoom()->Entites.size())
		CurAdjustmentEntityIndex = 0;

	CurAdjustmentEntity = World->GetRoom()->Entites[CurAdjustmentEntityIndex];
}

void ATileMapEditorMode::AddEntityLocation(FVector2D _AddPos)
{
	if (CurAdjustmentEntity == nullptr)
		return;

	CurAdjustmentEntity->AddEntityLocation(_AddPos);
}

void ATileMapEditorMode::AddEntitySpeed(float _Speed)
{
	AMoveEntity* Enermy = dynamic_cast<AMoveEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddSpeed(_Speed);
}

void ATileMapEditorMode::AddEntityMoveLenght(float _Lenght)
{
	AMoveEntity* Enermy = dynamic_cast<AMoveEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddMoveLenght(_Lenght);
}

void ATileMapEditorMode::AddEntityMoveOffSet(float _Offset)
{
	AMoveEntity* Enermy = dynamic_cast<AMoveEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddMoveLenghtOffset(_Offset);
}

void ATileMapEditorMode::AddEntityDir(FVector2D _Dir)
{
	AMoveEntity* Enermy = dynamic_cast<AMoveEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddDir(_Dir);
}

void ATileMapEditorMode::SetEntityDir(FVector2D _Dir)
{
	AMoveEntity* Enermy = dynamic_cast<AMoveEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->SetDir(_Dir);
}