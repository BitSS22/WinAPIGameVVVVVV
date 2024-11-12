#include "pch.h"
#include "TileMapEditorMode.h"
#include "Player.h"
#include "Enermy.h"
#include "Entity.h"

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

	// 커서 스프라이트
	CurSelectSprite = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectSprite->SetSprite("CollisionTiles::01 Type00 Cyan", 45);
	CurSelectSprite->SetComponentScale(EGameConst::TileScale);
	CurSelectSprite->SetOrder(ERenderOrder::EDITOR_CURSOR);

	CurSelectEntityType = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectEntityType->SetSprite("Enemies::001 Stop Cyan", 0);
	FVector2D SpriteSize = UImageManager::GetInst().FindSprite("Enemies::001 Stop Cyan")->GetSpriteData(0).Transform.Scale;
	CurSelectEntityType->SetComponentScale(SpriteSize);
	CurSelectEntityType->SetOrder(ERenderOrder::EDITOR_CURSOR);
	

	// Set Debug
	UEngineDebug::SetIsDebug(true);
}

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	// 프레임 표시
	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));

	// 마우스 위치 추적
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	// 타일 크기와 사이즈
	FIntPoint TileSize = World->GetRoom()->TileScale;
	FIntPoint TileCount = World->GetRoom()->TileCount;

	// 마우스 타일 격자 표시
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

	if (KEY_DOWN('1'))
		PrevTileList();

	if (KEY_DOWN('2'))
		NextTileList();

	if (KEY_DOWN('Q'))
		PrevTileSet();

	if (KEY_DOWN('W'))
		NextTileSet();

	if (KEY_DOWN('A'))
		PrevTile();

	if (KEY_DOWN('S'))
		NextTile();

	if (KEY_DOWN('X'))
		ShowTiles();

	if (KEY_DOWN('Z'))
		ShowBackGroundTiles();

	if (KEY_DOWN('D'))
		PickUpTile();

	if (KEY_DOWN('O'))
		PrevBackGroundImage();

	if (KEY_DOWN('P'))
		NextBackGroundImage();

	FIntPoint RoomIndex = World->CurRoomIndex;
	if (KEY_DOWN(VK_UP))
	{
		RoomIndex.Y -= 1;
		World->MoveRoom(RoomIndex);
	}
	if (KEY_DOWN(VK_DOWN))
	{
		RoomIndex.Y += 1;
		World->MoveRoom(RoomIndex);
	}
	if (KEY_DOWN(VK_LEFT))
	{
		RoomIndex.X -= 1;
		World->MoveRoom(RoomIndex);
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		RoomIndex.X += 1;
		World->MoveRoom(RoomIndex);
	}

	if (KEY_DOWN(VK_SPACE))
		CreateEntity();

	if (KEY_DOWN('N'))
		AddEntityLocation(FVector2D(16.f, 16.f));


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

	// Auto Tile은 주변 3X3 타일을 조사한다.
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

	// Auto Tile은 주변 3X3 타일을 조사한다.
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
	// 리소스 리스트 만들기
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
	str += ", ";
	str += std::to_string(RoomIndex.Y);
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
		str = "Selected Entity Name : ";
		str += CurAdjustmentEntity->GetRenderer()->GetCurSpriteName();
		str += ", List Number : ";
		str += std::to_string(CurAdjustmentEntityIndex);
		UEngineDebug::CoreOutputString(str);

		AEnermy* Enermy = dynamic_cast<AEnermy*>(CurAdjustmentEntity);
		if (Enermy != nullptr)
		{
			str = "Location : ";
			str += std::to_string(Enermy->GetEntityDefualtLocation().X);
			str += ", ";
			str += std::to_string(Enermy->GetEntityDefualtLocation().Y);
			str += ", MoveLenght : ";
			str += std::to_string(Enermy->GetMoveLenght());
			UEngineDebug::CoreOutputString(str);

			str = "Speed : ";
			str += std::to_string(Enermy->GetSpeed());
			str += ", StartOffset : ";
			str += std::to_string(Enermy->GetMoveLenghtOffset());
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
	if (CurSelectObjectList == EntityList::Enemies)
	{
		AEnermy* NewEntity = GetWorld()->SpawnActor<AEnermy>();
		NewEntity->EnermyDefaultSetUp(CurSelectEntityType->GetCurSpriteName(), CurSelectEntityType->GetComponentLocation(), FVector2D::RIGHT, EGameConst::DefualtSpeed, EGameConst::DefualtMoveLen, 0.f);
		World->GetRoom()->Enties.push_back(NewEntity);
		CurAdjustmentEntity = NewEntity;
		CurAdjustmentEntityIndex = World->GetRoom()->Enties.size() - 1;
	}
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

void ATileMapEditorMode::AddEntityLocation(FVector2D _AddPos)
{
	if (CurAdjustmentEntity == nullptr)
		return;

	AEnermy* Enermy = dynamic_cast<AEnermy*>(CurAdjustmentEntity);

	if (Enermy != nullptr)
		Enermy->AddEntityLocation(_AddPos);
	else
		CurAdjustmentEntity->AddEntityLocation(_AddPos);
}

void ATileMapEditorMode::AddEntitySpeed(float _Speed)
{
	AEnermy* Enermy = dynamic_cast<AEnermy*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddSpeed(_Speed);
}

void ATileMapEditorMode::SetEntityDir(FVector2D _Dir)
{
	AEnermy* Enermy = dynamic_cast<AEnermy*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->SetDir(_Dir);
}

void ATileMapEditorMode::AddEntityMoveLenght(float _Lenght)
{
	AEnermy* Enermy = dynamic_cast<AEnermy*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddMoveLenght(_Lenght);
}

void ATileMapEditorMode::AddEntityMoveOffSet(float _Offset)
{
	AEnermy* Enermy = dynamic_cast<AEnermy*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddMoveLenghtOffset(_Offset);
}
