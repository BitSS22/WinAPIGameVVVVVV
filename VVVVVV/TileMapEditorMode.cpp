#include "pch.h"
#include "TileMapEditorMode.h"
#include "Player.h"
#include "PistonEntity.h"
#include "Entity.h"
#include "GameWorld.h"

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

	GameWorld = GetWorld()->SpawnActor<AGameWorld>();

	// 커서 스프라이트
	CurSelectTile = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectTile->SetSprite("CollisionTiles::Type00-1 Cyan", 44);
	CurSelectTile->SetComponentScale(EGameConst::TileScale);
	CurSelectTile->SetOrder(ERenderOrder::EDITOR_CURSOR);

	CurSelectEntityType = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectEntityType->SetSprite("Enemies::001 Stop Cyan", 0);
	FVector2D SpriteSize = UImageManager::GetInst().FindSprite("Enemies::001 Stop Cyan")->GetSpriteData(0).Transform.Scale;
	CurSelectEntityType->SetComponentScale(SpriteSize);
	CurSelectEntityType->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	CurSelectEntityType->SetOrder(ERenderOrder::EDITOR_CURSOR);
	CurSelectEntityType->SetActive(false);

	GameWorld->SetEditMode(true);
	GameWorld->LoadFile();

	// Set Debug
	UEngineDebug::SetIsDebug(true);
}

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	// 프레임 표시
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

	return FindAroundTile(Bools);
}

int ATileMapEditorMode::FindAroundTile(uint8_t _Bit) const
{
	int Result = -1;

	switch (_Bit)
	{
	case 0b0000'0000: // 인접 없음
		Result = 39;
		break;

	case 0b0000'0010: // 위쪽만
		Result = 27;
		break;
	case 0b0000'1000: // 왼쪽만
		Result = 38;
		break;
	case 0b0001'0000: // 오른쪽만
		Result = 36;
		break;
	case 0b0100'0000: // 아래쪽만
		Result = 3;
		break;

	case 0b0100'0010: // 위쪽 아래쪽만
		Result = 15;
		break;
	case 0b0001'1000: // 왼쪽 오른쪽만
		Result = 37;
		break;

	case 0b0000'1011: // 위쪽 왼쪽 + 사이
		Result = 26;
		break;
	case 0b0000'1010:
		Result = 17;
		break;
	case 0b0001'0110: // 위쪽 오른쪽 + 사이
		Result = 24;
		break;
	case 0b0001'0010:
		Result = 16;
		break;
	case 0b0110'1000: // 아래쪽 왼쪽 + 사이
		Result = 2;
		break;
	case 0b0100'1000:
		Result = 5;
		break;
	case 0b1101'0000: // 아래쪽 오른쪽 + 사이
		Result = 0;
		break;
	case 0b0101'0000:
		Result = 4;
		break;

	case 0b0001'1011: // 위쪽 왼쪽 오른쪽 + 사이
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
	case 0b0100'1011: // 위쪽 왼쪽 아래쪽 + 사이
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
	case 0b0101'0110: // 위쪽 오른쪽 아래쪽 + 사이
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
	case 0b1101'1000: // 왼쪽 오른쪽 아래쪽 + 사이
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

	case 0b0101'1011:  // 네 방향 + 사이 없음
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
		MSGASSERT(nullptr, "타일 알고리즘이 이상합니다.");

	return Result;
}

bool ATileMapEditorMode::IsSameTileName(const string& _Name, int _x, int _y) const
{
	auto& CurSelectTileMap = GetCurSelectTileMap();

	if (_x < 0 || _y < 0 || _x >= GameWorld->GetRoom()->TileCount.X || _y >= GameWorld->GetRoom()->TileCount.Y)
		return true;
	else if (CurSelectTileMap[_y][_x]->GetCurSpriteName() == _Name)
		return true;

	return false;
}

void ATileMapEditorMode::ChangeTile(bool _AroundTileChange, FIntPoint _Index)
{
	auto& CurSelectTileMap = GetCurSelectTileMap();

	FIntPoint TileCount = GameWorld->GetRoom()->TileCount;

	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	if (CursorPos.X < 0 || CursorPos.Y < 0 || CursorPos.X >= WindowSize.X || CursorPos.Y >= WindowSize.Y)
		return;

	int MaxIndex = CurSelectTile->GetMaxIndex();

	CurSelectTileMap[_Index.Y][_Index.X]->SetSprite(CurSelectTile->GetCurSpriteName(), CurSelectTile->GetCurIndex());
	CurSelectTileMap[_Index.Y][_Index.X]->ChangeAnimation(CurSelectTile->GetCurSpriteName(), false);

	// Auto Tile은 주변 3X3 타일을 조사한다.
	if ((_AroundTileChange || CurSelectTile->GetCurIndex() == 45) && MaxIndex >= 47)
	{
		for (int y = _Index.Y - 1; y <= _Index.Y + 1; ++y)
		{
			for (int x = _Index.X - 1; x <= _Index.X + 1; ++x)
			{
				if (IsSameTileName(CurSelectTile->GetCurSpriteName(), x, y))
				{
					if (x < 0 || y < 0 || x >= TileCount.X || y >= TileCount.Y)
						continue;
					CurSelectTileMap[y][x]->SetSprite(CurSelectTile->GetCurSpriteName(), AroundTileChange(CurSelectTile->GetCurSpriteName(), x, y));
				}
			}
		}
	}
}

void ATileMapEditorMode::DeleteTile(bool _AroundTileChange, FIntPoint _Index)
{
	auto& CurSelectTileMap = GetCurSelectTileMap();

	FIntPoint TileCount = GameWorld->GetRoom()->TileCount;

	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	if (CursorPos.X < 0 || CursorPos.Y < 0 || CursorPos.X >= WindowSize.X || CursorPos.Y >= WindowSize.Y)
		return;

	string PrevName = CurSelectTileMap[_Index.Y][_Index.X]->GetCurSpriteName();
	int MaxIndex = CurSelectTileMap[_Index.Y][_Index.X]->GetMaxIndex();

	CurSelectTileMap[_Index.Y][_Index.X]->SetSprite("None Tile", 0);

	// Auto Tile은 주변 3X3 타일을 조사한다.
	if ((_AroundTileChange || CurSelectTile->GetCurIndex() == 45) && MaxIndex >= 47)
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

	GameWorld->GetRoom()->MoveRoom(_Index);
}

void ATileMapEditorMode::SwitchLoopRoom()
{
	FIntPoint Index = GameWorld->CurRoomIndex;
	bool& IsLoop = GameWorld->RoomDatas[Index.Y][Index.X].LoopRoom;
	IsLoop = !IsLoop;
}

void ATileMapEditorMode::NextTileList()
{
	++CurTileList;
	CurSelectTile->SetSprite(TileLists[static_cast<int>(CurTileList)][0], 0);
	CurTileSetIndex = 0;
}

void ATileMapEditorMode::PrevTileList()
{
	--CurTileList;
	CurSelectTile->SetSprite(TileLists[static_cast<int>(CurTileList)][0], 0);
	CurTileSetIndex = 0;
}

void ATileMapEditorMode::PrevTileSet()
{
	--CurTileSetIndex;
	if (CurTileSetIndex < 0 || CurTileSetIndex >= TileLists[static_cast<int>(CurTileList)].size())
		CurTileSetIndex = static_cast<int>(TileLists[static_cast<int>(CurTileList)].size()) - 1;

	int Curindex = CurSelectTile->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(TileLists[static_cast<int>(CurTileList)][CurTileSetIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectTile->SetSprite(TileLists[static_cast<int>(CurTileList)][CurTileSetIndex], Curindex);
}

void ATileMapEditorMode::NextTileSet()
{
	++CurTileSetIndex;
	if (CurTileSetIndex < 0 || CurTileSetIndex >= TileLists[static_cast<int>(CurTileList)].size())
		CurTileSetIndex = 0;

	int Curindex = CurSelectTile->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(TileLists[static_cast<int>(CurTileList)][CurTileSetIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectTile->SetSprite(TileLists[static_cast<int>(CurTileList)][CurTileSetIndex], Curindex);
}

void ATileMapEditorMode::PrevTile()
{
	int index = CurSelectTile->GetCurIndex();
	--index;
	if (index < 0 || index >= CurSelectTile->GetMaxIndex())
		index = CurSelectTile->GetMaxIndex() - 1;
	CurSelectTile->SetSprite(CurSelectTile->GetCurSpriteName(), index);
}

void ATileMapEditorMode::NextTile()
{
	int index = CurSelectTile->GetCurIndex();
	++index;
	if (index < 0 || index >= CurSelectTile->GetMaxIndex())
		index = 0;
	CurSelectTile->SetSprite(CurSelectTile->GetCurSpriteName(), index);
}

void ATileMapEditorMode::ShowTiles()
{
	auto& room = GameWorld->GetRoom()->Tiles;
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
	auto& room = GameWorld->GetRoom()->BackGroundTiles;
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
	FIntPoint TileIndex = GameWorld->GetRoom()->GetOnTileIndex(UEngineAPICore::GetCore()->GetMainWindow().GetMousePos());
	if (TileIndex.X < 0 || TileIndex.X >= GameWorld->GetRoom()->TileCount.X || TileIndex.Y < 0 || TileIndex.Y >= GameWorld->GetRoom()->TileCount.Y)
		return;
	auto& SelectTileMap = GetCurSelectTileMap();
	CurSelectTile->SetSprite(SelectTileMap[TileIndex.Y][TileIndex.X]->GetCurSpriteName(), SelectTileMap[TileIndex.Y][TileIndex.X]->GetCurIndex());
}

void ATileMapEditorMode::LoadResourceList()
{
	// 리소스 리스트 만들기
	const auto& SpritesList = UImageManager::GetInst().ViewSprites();

	string BackGroundTiles = UEngineString::ToUpper("BackGroundTiles::");
	string CollisionTiles = UEngineString::ToUpper("CollisionTiles::");
	string SpikeTiles = UEngineString::ToUpper("SpikeTiles::");
	string AnimationTiles = UEngineString::ToUpper("AnimationTiles::");
	string RailTiles = UEngineString::ToUpper("RailTiles::");

	string BackGrounds = UEngineString::ToUpper("BackGrounds::");

	string APlatform = UEngineString::ToUpper("Platforms::");
	string Saves = UEngineString::ToUpper("Saves::");
	string Enemies = UEngineString::ToUpper("Enemies::");

	for (auto& Sprite : SpritesList)
	{
		if (std::string::npos != Sprite.first.find(BackGroundTiles))
			TileLists[static_cast<int>(TileList::BackGroundTileList)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(CollisionTiles))
			TileLists[static_cast<int>(TileList::TileList)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(SpikeTiles))
			TileLists[static_cast<int>(TileList::SpikeTileList)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(AnimationTiles))
			TileLists[static_cast<int>(TileList::AnimationTileList)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(RailTiles))
			TileLists[static_cast<int>(TileList::RailTileList)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(BackGrounds))
			TileLists[static_cast<int>(TileList::BackGroundList)].push_back(Sprite.first);

		else if (std::string::npos != Sprite.first.find(APlatform))
			EntityLists[static_cast<int>(EntityList::Platforms)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(Saves))
			EntityLists[static_cast<int>(EntityList::Saves)].push_back(Sprite.first);
		else if (std::string::npos != Sprite.first.find(Enemies))
			EntityLists[static_cast<int>(EntityList::Enemies)].push_back(Sprite.first);
	}
}

void ATileMapEditorMode::EditorKeyCheck()
{
	// 마우스 위치 추적
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	// 타일 크기와 사이즈
	FIntPoint TileSize = GameWorld->GetRoom()->TileScale;
	FIntPoint TileCount = GameWorld->GetRoom()->TileCount;

	// 마우스 타일 격자 표시
	FIntPoint TileCursorPos = FIntPoint(CursorPos.X - (CursorPos.X % TileSize.X) + TileSize.X / 2, CursorPos.Y - (CursorPos.Y % TileSize.Y) + TileSize.Y / 2);
	CurSelectTile->SetComponentLocation(FVector2D(TileCursorPos.fX(), TileCursorPos.fY()));

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

	// Tile 관련

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

	// 배경화면
	if (KEY_DOWN('O'))
		PrevBackGroundImage();
	if (KEY_DOWN('P'))
		NextBackGroundImage();

	// 방 이동, 세이브
	FIntPoint RoomIndex = GameWorld->CurRoomIndex;
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

	// Entity 관련
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
		GameWorld->SaveFile();

	if (KEY_DOWN(VK_F4))
		GameWorld->LoadFile();

	if (KEY_DOWN(VK_TAB))
		SwitchLoopRoom();
}

void ATileMapEditorMode::DebugText()
{
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FIntPoint RoomIndex = GameWorld->CurRoomIndex;

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
	if (GameWorld->RoomDatas[GameWorld->CurRoomIndex.Y][GameWorld->CurRoomIndex.X].LoopRoom == true)
		str += "True";
	else
		str += "False";
	UEngineDebug::CoreOutputString(str);

	str = "Tile Set Index : ";
	str += std::to_string(CurTileSetIndex);
	UEngineDebug::CoreOutputString(str);

	str = "Select Tile Name : ";
	str += CurSelectTile->GetCurSpriteName();
	str += ", Index : ";
	str += std::to_string(CurSelectTile->GetCurIndex());
	UEngineDebug::CoreOutputString(str);

	FIntPoint TileCursorIndex = GameWorld->GetRoom()->GetOnTileIndex(CursorPos);
	if ((TileCursorIndex.X < 0 || TileCursorIndex.X >= GameWorld->GetRoom()->TileCount.X || TileCursorIndex.Y < 0 || TileCursorIndex.Y >= GameWorld->GetRoom()->TileCount.Y) == false)
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

		APistonEntity* MoveEntity = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);
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

	GameWorld->GetRoom()->BackGround->SetBackGround(TileLists[static_cast<int>(TileList::BackGroundList)][CurBackGroundIndex]);
}

void ATileMapEditorMode::NextBackGroundImage()
{
	++CurBackGroundIndex;
	if (CurBackGroundIndex >= TileLists[static_cast<int>(TileList::BackGroundList)].size())
		CurBackGroundIndex = 0;

	GameWorld->GetRoom()->BackGround->SetBackGround(TileLists[static_cast<int>(TileList::BackGroundList)][CurBackGroundIndex]);
}

void ATileMapEditorMode::CreateEntity()
{
	if (CurEntityList == EntityList::Enemies || CurEntityList == EntityList::Platforms)
	{
		APistonEntity* NewEntity = GetWorld()->SpawnActor<APistonEntity>();
		NewEntity->MoveEntityDefaultSetUp(CurSelectEntityType->GetCurSpriteName(), CurSelectEntityType->GetComponentLocation(), FVector2D::RIGHT, EGameConst::DefualtSpeed, EGameConst::DefualtMoveLen, 0.f);
		NewEntity->SetRoom(GameWorld->GetRoom());
		GameWorld->GetRoom()->Entites.push_back(NewEntity);
		CurAdjustmentEntity = NewEntity;
		CurAdjustmentEntityIndex = static_cast<int>(GameWorld->GetRoom()->Entites.size() - 1);
	}
	else if (CurEntityList == EntityList::Saves)
	{
		// TODO. 
	}
}

void ATileMapEditorMode::DeleteEntity()
{
	if (CurAdjustmentEntity == nullptr)
		return;

	auto& Entites = GameWorld->GetRoom()->Entites;
	CurAdjustmentEntity->Destroy();
	Entites.erase(Entites.begin() + CurAdjustmentEntityIndex);
	--CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex == -1)
		CurAdjustmentEntity = nullptr;
	else
		CurAdjustmentEntity = Entites[CurAdjustmentEntityIndex];
}

void ATileMapEditorMode::PrevEntityList()
{
	++CurEntityList;
	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurEntityList)][0], 0);
	CurEntityIndex = 0;
}

void ATileMapEditorMode::NextEntityList()
{
	--CurEntityList;
	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurEntityList)][0], 0);
	CurEntityIndex = 0;
}

void ATileMapEditorMode::PrevEntityType(int _AddIndex)
{
	CurEntityIndex -= _AddIndex;
	if (CurEntityIndex < 0 || CurEntityIndex >= EntityLists[static_cast<int>(CurEntityList)].size())
		CurEntityIndex = static_cast<int>(EntityLists[static_cast<int>(CurEntityList)].size()) - 1;

	int Curindex = CurSelectEntityType->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(EntityLists[static_cast<int>(CurEntityList)][CurEntityIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurEntityList)][CurEntityIndex], Curindex);
}

void ATileMapEditorMode::NextEntityType(int _AddIndex)
{
	CurEntityIndex += _AddIndex;
	if (CurEntityIndex < 0 || CurEntityIndex >= EntityLists[static_cast<int>(CurEntityList)].size())
		CurEntityIndex = 0;

	int Curindex = CurSelectEntityType->GetCurIndex();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(EntityLists[static_cast<int>(CurEntityList)][CurEntityIndex]);

	if (Curindex >= Sprite->GetSpriteCount())
		Curindex = Sprite->GetSpriteCount() - 1;

	CurSelectEntityType->SetSprite(EntityLists[static_cast<int>(CurEntityList)][CurEntityIndex], Curindex);
}

void ATileMapEditorMode::PrevSelectEntity()
{
	if (GameWorld->GetRoom()->Entites.empty() == true)
		return;

	--CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex < 0)
		CurAdjustmentEntityIndex = static_cast<int>(GameWorld->GetRoom()->Entites.size() - 1);
	
	CurAdjustmentEntity = GameWorld->GetRoom()->Entites[CurAdjustmentEntityIndex];
}

void ATileMapEditorMode::NextSelectEntity()
{
	if (GameWorld->GetRoom()->Entites.empty() == true)
		return;

	++CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex >= GameWorld->GetRoom()->Entites.size())
		CurAdjustmentEntityIndex = 0;

	CurAdjustmentEntity = GameWorld->GetRoom()->Entites[CurAdjustmentEntityIndex];
}

void ATileMapEditorMode::AddEntityLocation(FVector2D _AddPos)
{
	if (CurAdjustmentEntity == nullptr)
		return;

	CurAdjustmentEntity->AddEntityLocation(_AddPos);
}

void ATileMapEditorMode::AddEntitySpeed(float _Speed)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddSpeed(_Speed);
}

void ATileMapEditorMode::AddEntityMoveLenght(float _Lenght)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddMoveLenght(_Lenght);
}

void ATileMapEditorMode::AddEntityMoveOffSet(float _Offset)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddMoveLenghtOffset(_Offset);
}

void ATileMapEditorMode::AddEntityDir(FVector2D _Dir)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddDir(_Dir);
}

void ATileMapEditorMode::SetEntityDir(FVector2D _Dir)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->SetDir(_Dir);
}