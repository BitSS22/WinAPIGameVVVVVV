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

	// Cursor Sprite
	CurSelectTile = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectTile->SetSprite("CollisionTiles::Type00-1 Cyan", 44);
	CurSelectTile->SetComponentScale(EGameConst::TileScale);
	CurSelectTile->SetOrder(ERenderOrder::EDITOR_CURSOR);

	// Entity Sprite
	CurSelectEntity = CreateDefaultSubObject<USpriteRenderer>();
	CurSelectEntity->SetSprite("Enemies::001 Stop Cyan", 0);
	FVector2D SpriteSize = UImageManager::GetInst().FindSprite("Enemies::001 Stop Cyan")->GetSpriteData(0).Transform.Scale;
	CurSelectEntity->SetComponentScale(SpriteSize);
	CurSelectEntity->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	CurSelectEntity->SetActive(false);
	// Set Debug
	UEngineDebug::SetIsDebug(true);
}

void ATileMapEditorMode::Tick()
{
	Super::Tick();

	EditorKeyCheck();


	// Show Frame
	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));

	// Debug
	DebugText();
}

int ATileMapEditorMode::GetCheckAroundTileIndex(string_view _Name, const FIntPoint& _Index) const
{
	uint8_t Bools = 0;

	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (IsSameTileName(_Name, FIntPoint(_Index.X + x, _Index.Y + y)) == true)
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

	int Result = -1;

	switch (Bools)
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

bool ATileMapEditorMode::IsSameTileName(string_view _Name, const FIntPoint& _Index) const
{
	if (AGameWorld::GetRoom()->IsOutTileIndex(_Index) == true)
		return true;
	else if (GetGameWorld()->GetRoom()->GetTilesCRef()[_Index.Y][_Index.X]->GetSpriteName() == _Name)
		return true;

	return false;
}

void ATileMapEditorMode::ChangeTile(bool _AroundTileChange, FIntPoint _Index)
{
	// Over Index Check
	if (AGameWorld::GetRoom()->IsOutTileIndex(_Index) == true)
		return;

	// Create Tile Data
	RoomTileData TileData = {};
	TileData.Name = CurSelectTile->GetCurSpriteName();
	TileData.CurIndex = CurSelectTile->GetCurIndex();
	TileData.TileType = CurTileType;

	// Index Tile Change
	const vector<vector<ATile*>>& Tiles = GetGameWorld()->GetRoom()->GetTilesCRef();
	Tiles[_Index.Y][_Index.X]->SetTile(TileData);

	// Around Tile Change
	if ((_AroundTileChange || TileData.CurIndex == 45) && CurSelectTile->GetMaxIndex() >= 47)
	{
		for (int y = _Index.Y - 1; y <= _Index.Y + 1; ++y)
		{
			for (int x = _Index.X - 1; x <= _Index.X + 1; ++x)
			{
				if (IsSameTileName(TileData.Name, FIntPoint(x, y)))
				{
					if (x < 0 || y < 0 || x >= EGameConst::TileCount.X || y >= EGameConst::TileCount.Y)
						continue;
					TileData.CurIndex = GetCheckAroundTileIndex(TileData.Name, FIntPoint(x, y));
					Tiles[y][x]->SetTile(TileData);
				}
			}
		}
	}
}

void ATileMapEditorMode::DeleteTile(bool _AroundTileChange, FIntPoint _Index)
{
	// Over Index Check
	if (AGameWorld::GetRoom()->IsOutTileIndex(_Index) == true)
		return;

	// Create Tile Data
	RoomTileData TileData = {};
	TileData.Name = "NoneTiles::None";
	TileData.CurIndex = 0;
	TileData.TileType = ETileType::None;

	// Index Tile Change, Prev Tile Data Save
	const vector<vector<ATile*>>& Tiles = GetGameWorld()->GetRoom()->GetTilesCRef();

	RoomTileData PrevTileData = Tiles[_Index.Y][_Index.X]->GetTileData();
	UEngineSprite* PrevSprite = UImageManager::GetInst().FindSprite(PrevTileData.Name);

	Tiles[_Index.Y][_Index.X]->SetTile(TileData);

	// Around Tile Change
	if ((_AroundTileChange || CurSelectTile->GetCurIndex() == 45) && PrevSprite->GetSpriteCount() >= 47)
	{
		for (int y = _Index.Y - 1; y <= _Index.Y + 1; ++y)
		{
			for (int x = _Index.X - 1; x <= _Index.X + 1; ++x)
			{
				if (IsSameTileName(PrevSprite->GetNameView(), FIntPoint(x, y)))
				{
					if (x < 0 || y < 0 || x >= EGameConst::TileCount.X || y >= EGameConst::TileCount.Y)
						continue;
					PrevTileData.CurIndex = GetCheckAroundTileIndex(PrevSprite->GetNameView(), FIntPoint(x, y));
					Tiles[y][x]->SetTile(PrevTileData);
				}
			}
		}
	}
}

void ATileMapEditorMode::MoveRoom(FIntPoint _Index)
{
	GameWorld->SaveRoomData();
	ResetAdjustmentEntity();

	GameWorld->GetRoom()->MoveRoom(_Index);

	USoundPlayer& BGMRef = AGameWorld::GetRoom()->BGM;
	string& NextBGMRef = AGameWorld::GetRoom()->NextBGM;

	if (BGMRef.GetCurrentSoundName() == NextBGMRef)
		NextBGMRef = "NONE";
	if (NextBGMRef.empty() == true)
	{
		BGMRef.Stop();
		BGMRef.Clear();
		NextBGMRef = "NONE";
	}
	else if (NextBGMRef.empty() == false && NextBGMRef != "NONE")
	{
		BGMRef.Stop();
		BGMRef = UEngineSound::Play(NextBGMRef);
		BGMRef.Loop();
		NextBGMRef = "NONE";
	}
}

void ATileMapEditorMode::SwitchLoopRoom()
{
	GameWorld->GetRoom()->SetIsLoop(!GameWorld->GetRoom()->GetIsLoop());
}

void ATileMapEditorMode::SetTileType(ETileType _Type)
{
	CurTileType = _Type;
	CurTileIndex = 0;

	CurSelectTile->SetSprite(TileDatas[static_cast<int>(CurTileType)][CurTileIndex].Name, 0);
}

void ATileMapEditorMode::AddTileList(int _Value)
{
	CurTileIndex += _Value;

	if (CurTileIndex < 0)
		CurTileIndex = static_cast<int>(TileDatas[static_cast<int>(CurTileType)].size() - 1);
	else if (CurTileIndex >= TileDatas[static_cast<int>(CurTileType)].size())
		CurTileIndex = 0;

	CurSelectTile->SetSprite(TileDatas[static_cast<int>(CurTileType)][CurTileIndex].Name, 0);
}

void ATileMapEditorMode::AddTileSpriteIndex(int _Value)
{
	int MaxIndex = CurSelectTile->GetMaxIndex();
	int CurIndex = CurSelectTile->GetCurIndex();
	CurIndex += _Value;
	if (CurIndex < 0)
		CurIndex = MaxIndex - 1;
	else if (CurIndex >= MaxIndex)
		CurIndex = 0;
	CurSelectTile->SetSprite(CurSelectTile->GetCurSpriteName(), CurIndex);
}

void ATileMapEditorMode::SetBackGroundType(EBackGroundType _Type)
{
	CurBackGroundType = _Type;
	CurBackGroundIndex = 0;

	const RoomBackGroundData& Data = BackGroundDatas[static_cast<int>(CurBackGroundType)][0];
	GameWorld->GetRoom()->GetBackGround()->SetBackGround(Data);
}

void ATileMapEditorMode::AddBackGroundList(int _Value)
{
	CurBackGroundIndex += _Value;
	if (CurBackGroundIndex < 0)
		CurBackGroundIndex = static_cast<int>(BackGroundDatas[static_cast<int>(CurBackGroundType)].size() - 1);
	else if (CurBackGroundIndex >= BackGroundDatas[static_cast<int>(CurBackGroundType)].size())
		CurBackGroundIndex = 0;

	const RoomBackGroundData& Data = BackGroundDatas[static_cast<int>(CurBackGroundType)][CurBackGroundIndex];
	GameWorld->GetRoom()->GetBackGround()->SetBackGround(Data);
}

void ATileMapEditorMode::AddBackGroundIndex(int _Value)
{
	RoomBackGroundData Data = GameWorld->GetRoom()->GetBackGround()->GetBackGroundData();
	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(Data.Name);
	int MaxIndex = Sprite->GetSpriteCount();
	Data.Index += _Value;
	if (Data.Index < 0)
		Data.Index = MaxIndex - 1;
	else if (Data.Index >= MaxIndex)
		Data.Index = 0;
	GameWorld->GetRoom()->GetBackGround()->SetBackGround(Data);
}

void ATileMapEditorMode::SetEntityType(EEntityType _Type)
{
	CurEntityType = _Type;
	CurEntityIndex = 0;

	CurSelectEntity->SetSprite(EntityDatas[static_cast<int>(CurEntityType)][CurEntityIndex].Name, 0);
}

void ATileMapEditorMode::AddEntityList(int _Value)
{
	CurEntityIndex += _Value;

	if (CurEntityIndex < 0)
		CurEntityIndex = static_cast<int>(EntityDatas[static_cast<int>(CurEntityType)].size() - 1);
	else if (CurEntityIndex >= EntityDatas[static_cast<int>(CurEntityType)].size())
		CurEntityIndex = 0;

	CurSelectEntity->SetSprite(EntityDatas[static_cast<int>(CurEntityType)][CurEntityIndex].Name, 0);
}

void ATileMapEditorMode::AddBGMIndex(int _Value)
{
	CurBGMIndex += _Value;

	if (CurBGMIndex < 0)
		CurBGMIndex = static_cast<int>(BGMDatas.size() - 1);
	else
		CurBGMIndex %= static_cast<int>(BGMDatas.size());

	USoundPlayer& BGMRef = AGameWorld::GetRoom()->BGM;
	BGMRef.Stop();
	if (CurBGMIndex != 0)
	{
		BGMRef = UEngineSound::Play(BGMDatas[CurBGMIndex]);
		BGMRef.Loop();
	}
	else
		BGMRef.Clear();
	BGMRef.SetVolume(1.f);
}

void ATileMapEditorMode::PickUpTile()
{
	POINT MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	if (AGameWorld::GetRoom()->IsOutScreen(MousePos) != FVector2D::ZERO)
		return;

	FIntPoint TileIndex = GameWorld->GetRoom()->GetOnTileIndex(MousePos);
	ATile* Tile = GetGameWorld()->GetRoom()->GetTilesCRef()[TileIndex.Y][TileIndex.X];
	CurTileType = Tile->GetType();

	CurSelectTile->SetSprite(Tile->GetSpriteName(), Tile->GetSpriteCurIndex());
}

void ATileMapEditorMode::LoadResourceList()
{
	// 리소스 리스트 만들기
	const auto& Sprites = UImageManager::GetInst().ViewSprites();

	string NoneTiles = UEngineString::ToUpper("NoneTiles::");
	string BackGroundTiles = UEngineString::ToUpper("BackGroundTiles::");
	string CollisionTiles = UEngineString::ToUpper("CollisionTiles::");
	string SpikeTiles = UEngineString::ToUpper("SpikeTiles::");
	string AnimationTiles = UEngineString::ToUpper("AnimationTiles::");
	string RailTiles = UEngineString::ToUpper("RailTiles::");

	string BackGrounds = UEngineString::ToUpper("BackGrounds::");

	string Platform = UEngineString::ToUpper("Platforms::");
	string PlatformsHide = UEngineString::ToUpper("PlatformsHide::");
	string CheckPoints = UEngineString::ToUpper("CheckPoints::");
	string Enemies = UEngineString::ToUpper("Enemies::");
	string Guys = UEngineString::ToUpper("Guys::");
	string Teleports = UEngineString::ToUpper("Teleports::");
	string FlipLines = UEngineString::ToUpper("FlipLines::");

	for (auto& Sprite : Sprites)
	{
		// Tile
		if (Sprite.first.find(NoneTiles) != std::string::npos)
		{
			RoomTileData TileData = {};
			TileData.Name = Sprite.first;
			TileData.TileType = ETileType::None;
			TileDatas[static_cast<int>(ETileType::None)].push_back(TileData);
		}
		else if (Sprite.first.find(BackGroundTiles) != std::string::npos)
		{
			RoomTileData TileData = {};
			TileData.Name = Sprite.first;
			TileData.TileType = ETileType::BackGround;
			TileDatas[static_cast<int>(ETileType::BackGround)].push_back(TileData);
		}
		else if (Sprite.first.find(CollisionTiles) != std::string::npos)
		{
			RoomTileData TileData = {};
			TileData.Name = Sprite.first;
			TileData.TileType = ETileType::Collision;
			TileDatas[static_cast<int>(ETileType::Collision)].push_back(TileData);
		}
		else if (Sprite.first.find(SpikeTiles) != std::string::npos)
		{
			RoomTileData TileData = {};
			TileData.Name = Sprite.first;
			TileData.TileType = ETileType::Spike;
			TileDatas[static_cast<int>(ETileType::Spike)].push_back(TileData);
		}
		else if (Sprite.first.find(AnimationTiles) != std::string::npos)
		{
			RoomTileData TileData = {};
			TileData.Name = Sprite.first;
			TileData.TileType = ETileType::Animation;
			TileDatas[static_cast<int>(ETileType::Animation)].push_back(TileData);
		}
		else if (Sprite.first.find(RailTiles) != std::string::npos)
		{
			RoomTileData TileData = {};
			TileData.Name = Sprite.first;
			if (Sprite.first.find(UEngineString::ToUpper("Left")) != std::string::npos)
			{
				TileData.TileType = ETileType::RailLeft;
				TileDatas[static_cast<int>(ETileType::RailLeft)].push_back(TileData);
			}
			else if (Sprite.first.find(UEngineString::ToUpper("Right")) != std::string::npos)
			{
				TileData.TileType = ETileType::RailRight;
				TileDatas[static_cast<int>(ETileType::RailRight)].push_back(TileData);
			}
		}
		// BackGround
		else if (Sprite.first.find(BackGrounds) != std::string::npos)
		{
			RoomBackGroundData BackGroundData = {};
			BackGroundData.Name = Sprite.first;
			if (Sprite.first.find(UEngineString::ToUpper("Space")) != std::string::npos)
			{
				BackGroundData.BackGroundType = EBackGroundType::Space;
				BackGroundDatas[static_cast<int>(EBackGroundType::Space)].push_back(BackGroundData);
			}
			else if (Sprite.first.find(UEngineString::ToUpper("Horizontal")) != std::string::npos)
			{
				BackGroundData.BackGroundType = EBackGroundType::Horizontal;
				BackGroundDatas[static_cast<int>(EBackGroundType::Horizontal)].push_back(BackGroundData);
			}
			else if (Sprite.first.find(UEngineString::ToUpper("Vertical")) != std::string::npos)
			{
				BackGroundData.BackGroundType = EBackGroundType::Vertical;
				BackGroundDatas[static_cast<int>(EBackGroundType::Vertical)].push_back(BackGroundData);
			}
			else if (Sprite.first.find(UEngineString::ToUpper("Tower")) != std::string::npos)
			{
				BackGroundData.BackGroundType = EBackGroundType::Tower;
				BackGroundDatas[static_cast<int>(EBackGroundType::Tower)].push_back(BackGroundData);
			}
			else if (Sprite.first.find(UEngineString::ToUpper("Ending")) != std::string::npos)
			{
				BackGroundData.BackGroundType = EBackGroundType::Ending;
				BackGroundDatas[static_cast<int>(EBackGroundType::Ending)].push_back(BackGroundData);
			}
			else if (Sprite.first.find(UEngineString::ToUpper("Maze")) != std::string::npos)
			{
				BackGroundData.BackGroundType = EBackGroundType::Maze;
				BackGroundDatas[static_cast<int>(EBackGroundType::Maze)].push_back(BackGroundData);
			}

		}
		// Entity
		else if (Sprite.first.find(Platform) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::Platform;
			EntityDatas[static_cast<int>(EEntityType::Platform)].push_back(EntityData);
		}
		else if (Sprite.first.find(PlatformsHide) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::PlatformHide;
			EntityDatas[static_cast<int>(EEntityType::PlatformHide)].push_back(EntityData);
		}
		else if (Sprite.first.find(CheckPoints) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::CheckPoint;
			EntityDatas[static_cast<int>(EEntityType::CheckPoint)].push_back(EntityData);
		}
		else if (Sprite.first.find(Enemies) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::Enermy;
			EntityDatas[static_cast<int>(EEntityType::Enermy)].push_back(EntityData);
		}
		else if (Sprite.first.find(Guys) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::Guy;
			EntityDatas[static_cast<int>(EEntityType::Guy)].push_back(EntityData);
		}
		else if (Sprite.first.find(Teleports) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::Teleport;
			EntityDatas[static_cast<int>(EEntityType::Teleport)].push_back(EntityData);
		}
		else if (Sprite.first.find(FlipLines) != std::string::npos)
		{
			RoomEntityData EntityData = {};
			EntityData.Name = Sprite.first;
			EntityData.EntityType = EEntityType::FlipLine;
			EntityDatas[static_cast<int>(EEntityType::FlipLine)].push_back(EntityData);
		}
	}

	BGMDatas.push_back("");
	BGMDatas.push_back("00 Potential for Anything Remixed.mp3");
	BGMDatas.push_back("01 Power-up.mp3");
	BGMDatas.push_back("02 Presenting VVVVVV.mp3");
	BGMDatas.push_back("03 Pause.mp3");
	BGMDatas.push_back("04 Pushing Onwards.mp3");
	BGMDatas.push_back("05 Path Complete.mp3");
	BGMDatas.push_back("06 Passion For Exploring.mp3");
	BGMDatas.push_back("07 Positive Force.mp3");
	BGMDatas.push_back("08 Predestined Fate.mp3");
	BGMDatas.push_back("09 Phear.mp3");
	BGMDatas.push_back("10 Potential For Anything.mp3");
	BGMDatas.push_back("11 Pressure Cooker.mp3");
	BGMDatas.push_back("12 Plenary.mp3");
	BGMDatas.push_back("13 Pipe Dream.mp3");
	BGMDatas.push_back("14 Popular Potpourri.mp3");
	BGMDatas.push_back("15 Positive Force Reversed.mp3");
	BGMDatas.push_back("16 Waiting For VVVVVV.mp3");
}

void ATileMapEditorMode::EditorKeyCheck()
{
	// 마우스 위치 추적
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

	// 타일 크기와 사이즈
	FIntPoint TileSize = EGameConst::TileScale;
	FIntPoint TileCount = EGameConst::TileCount;

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
	if (KEY_DOWN(VK_XBUTTON1) || KEY_DOWN('I'))
		PickUpTile();

	if (KEY_DOWN(VK_XBUTTON2) || KEY_DOWN(VK_END))
	{
		if (KEY_PRESS(VK_CONTROL))
			AddTileSpriteIndex(-1);
		else
			AddTileSpriteIndex(1);
	}

	if (KEY_DOWN('1'))
		SetTileType(--CurTileType);
	if (KEY_DOWN('2'))
		SetTileType(++CurTileType);

	if (KEY_DOWN('Q'))
	{
		if (KEY_PRESS(VK_CONTROL))
			AddTileList(-7);
		else
			AddTileList(-1);
	}
	if (KEY_DOWN('E'))
	{
		if (KEY_PRESS(VK_CONTROL))
			AddTileList(7);
		else
			AddTileList(1);
	}

	// 배경화면
	if (KEY_DOWN('O'))
	{
		if (KEY_PRESS(VK_CONTROL))
			SetBackGroundType(--CurBackGroundType);
		else
			AddBackGroundIndex(-1);
	}
	if (KEY_DOWN('P'))
	{
		if (KEY_PRESS(VK_CONTROL))
			SetBackGroundType(++CurBackGroundType);
		else
			AddBackGroundIndex(1);
	}

	FVector2D Dir = FVector2D::ZERO;
	
	FIntPoint RoomIndex = AGameWorld::GetCurRoomIndex();
	if (KEY_DOWN('W'))
	{
		if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT))
		{
			RoomIndex.Y -= 1;
			MoveRoom(RoomIndex);
		}
		else
			Dir += FVector2D::UP;
	}
	if (KEY_DOWN('S'))
	{
		if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT))
		{
			RoomIndex.Y += 1;
			MoveRoom(RoomIndex);
		}
		else
			Dir += FVector2D::DOWN;
	}
	if (KEY_DOWN('A'))
	{
		if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT))
		{
			RoomIndex.X -= 1;
			MoveRoom(RoomIndex);
		}
		else
			Dir += FVector2D::LEFT;
	}
	if (KEY_DOWN('D'))
	{
		if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT))
		{
			RoomIndex.X += 1;
			MoveRoom(RoomIndex);
		}
		else
			Dir += FVector2D::RIGHT;
	}

	if (Dir != FVector2D::ZERO)
	{
		if (KEY_PRESS(VK_CONTROL) && KEY_FREE(VK_SHIFT))
			SetEntityDir(Dir);
		else
			AddEntityDir(Dir);
	}

	if (KEY_DOWN('R'))
		MoveRoom(RoomIndex);


	if (KEY_PRESS(VK_CONTROL))
		Dir += FVector2D::UP;
	else if (KEY_DOWN('J'))
		Dir += FVector2D::DOWN;
	else if (KEY_DOWN('H'))
		Dir += FVector2D::LEFT;
	else if (KEY_DOWN('K'))
		Dir += FVector2D::RIGHT;

	// BGM
	if (KEY_DOWN('7'))
		AddBGMIndex(-1);
	else if (KEY_DOWN('8'))
		AddBGMIndex(1);

	// Entity 관련
	if (KEY_DOWN(VK_RETURN))
		CreateEntity();
	if (KEY_DOWN(VK_DELETE))
		DeleteEntity();

	Dir = FVector2D::ZERO;

	if (KEY_DOWN(VK_UP))
	{
		if (KEY_PRESS(VK_SHIFT))
			Dir += FVector2D::UP * 1;
		else if (KEY_PRESS(VK_CONTROL))
			Dir += FVector2D::UP * 64;
		else
			Dir += FVector2D::UP * 8;
	}
	if (KEY_DOWN(VK_DOWN))
	{
		if (KEY_PRESS(VK_SHIFT))
			Dir += FVector2D::DOWN * 1;
		else if (KEY_PRESS(VK_CONTROL))
			Dir += FVector2D::DOWN * 64;
		else
			Dir += FVector2D::DOWN * 8;
	}
	if (KEY_DOWN(VK_LEFT))
	{
		if (KEY_PRESS(VK_SHIFT))
			Dir += FVector2D::LEFT * 1;
		else if (KEY_PRESS(VK_CONTROL))
			Dir += FVector2D::LEFT * 64;
		else
			Dir += FVector2D::LEFT * 8;
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		if (KEY_PRESS(VK_SHIFT))
			Dir += FVector2D::RIGHT * 1;
		else if (KEY_PRESS(VK_CONTROL))
			Dir += FVector2D::RIGHT * 64;
		else
			Dir += FVector2D::RIGHT * 8;
	}

	if (Dir != FVector2D::ZERO)
		AddEntityLocation(Dir);


	if (KEY_DOWN(VK_OEM_MINUS))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntitySpeed(-1.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntitySpeed(-64.f);
		else
			AddEntitySpeed(-8.f);
	}
	if (KEY_DOWN(VK_OEM_PLUS))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntitySpeed(1.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntitySpeed(64.f);
		else
			AddEntitySpeed(8.f);
	}

	if (KEY_DOWN(VK_OEM_4))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveLenght(-1.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveLenght(-64.f);
		else
			AddEntityMoveLenght(-8.f);
	}
	if (KEY_DOWN(VK_OEM_6))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveLenght(1.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveLenght(64.f);
		else
			AddEntityMoveLenght(8.f);
	}

	if (KEY_DOWN('9'))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveOffSet(-1.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveOffSet(-64.f);
		else
			AddEntityMoveOffSet(-8.f);
	}
	if (KEY_DOWN('0'))
	{
		if (KEY_PRESS(VK_SHIFT))
			AddEntityMoveOffSet(1.f);
		else if (KEY_PRESS(VK_CONTROL))
			AddEntityMoveOffSet(64.f);
		else
			AddEntityMoveOffSet(8.f);
	}

	if (KEY_DOWN('N'))
		PrevSelectEntity();
	if (KEY_DOWN('M'))
		NextSelectEntity();

	if (KEY_DOWN('3'))
		SetEntityType(--CurEntityType);
	if (KEY_DOWN('4'))
		SetEntityType(++CurEntityType);

	if (KEY_DOWN('Z'))
	{
		if (KEY_PRESS(VK_CONTROL))
			AddEntityList(-7);
		else
			AddEntityList(-1);
	}
	if (KEY_DOWN('C'))
	{
		if (KEY_PRESS(VK_CONTROL))
			AddEntityList(7);
		else
			AddEntityList(1);
	}

	if (KEY_DOWN(VK_F3))
	{
		GameWorld->SaveMapFile();
	}

	if (KEY_DOWN(VK_F4))
	{
		ResetAdjustmentEntity();
		GameWorld->LoadMapFile();
		FIntPoint CurRoomIndex = AGameWorld::GetCurRoomIndex();
		GameWorld->GetRoom()->SetRoom(AGameWorld::GetRoomDatasRef(CurRoomIndex));
	}

	if (KEY_DOWN(VK_TAB))
		SwitchLoopRoom();
}

void ATileMapEditorMode::DebugText()
{
	FIntPoint CursorPos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FIntPoint RoomIndex = AGameWorld::GetCurRoomIndex();

	// DEBUG TEXT

	string str = "";

	str = "Current BGM Name : ";
	if (AGameWorld::GetRoom()->BGM.IsPlaying() == true)
		str += AGameWorld::GetRoom()->BGM.GetCurrentSoundName();
	else
		str += "None BGM";
	UEngineDebug::CoreOutputString(str);


	str = "World Index : ";
	str += std::to_string(RoomIndex.X);
	str += ",";
	str += std::to_string(RoomIndex.Y);
	str += ", RoomLoop : ";
	if (GameWorld->GetRoom()->GetIsLoop() == true)
		str += "true";
	else
		str += "false";
	UEngineDebug::CoreOutputString(str);

	str = "Current Entity Name : ";
	str += CurSelectEntity->GetCurSpriteName();
	UEngineDebug::CoreOutputString(str);

	str = "Currnet Tile Name : ";
	str += CurSelectTile->GetCurSpriteName();
	str += ", Index : ";
	str += std::to_string(CurSelectTile->GetCurIndex());
	UEngineDebug::CoreOutputString(str);

	FIntPoint TileCursorIndex = GameWorld->GetRoom()->GetOnTileIndex(CursorPos);
	if (GameWorld->GetRoom()->IsOutTileIndex(TileCursorIndex) == false)
	{
		str = "CursorIndex : ";
		str += std::to_string(TileCursorIndex.X);
		str += ",";
		str += std::to_string(TileCursorIndex.Y);
		str += ", On Tile Name : ";
		str += GameWorld->GetRoom()->GetTilesCRef()[TileCursorIndex.Y][TileCursorIndex.X]->GetSpriteName();
		str += ", TileIndex : ";
		str += std::to_string(GameWorld->GetRoom()->GetTilesCRef()[TileCursorIndex.Y][TileCursorIndex.X]->GetSpriteCurIndex());
		UEngineDebug::CoreOutputString(str);
	}

	if (CurAdjustmentEntity != nullptr)
	{
		FTransform Trans = CurAdjustmentEntity->GetActorTransform();
		Trans.Scale = FVector2D((Trans.Scale.X + Trans.Scale.Y) / 1.3f, (Trans.Scale.X + Trans.Scale.Y) / 1.3f);
		UEngineDebug::CoreDebugRender(Trans, UEngineDebug::EDebugPosType::Circle);

		str = "Selected Entity Name : ";
		str += CurAdjustmentEntity->GetSpriteName();
		str += ", Number : ";
		str += std::to_string(CurAdjustmentEntityIndex);
		UEngineDebug::CoreOutputString(str);

		str = "Location : ";
		str += std::to_string(CurAdjustmentEntity->GetEntityLocation().X);
		str += ",";
		str += std::to_string(CurAdjustmentEntity->GetEntityLocation().Y);
		str += ", Scale : ";
		str += std::to_string(CurAdjustmentEntity->GetActorScale().X);
		str += ",";
		str += std::to_string(CurAdjustmentEntity->GetActorScale().Y);
		UEngineDebug::CoreOutputString(str);

		APistonEntity* PistonEntity = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);
		if (PistonEntity != nullptr)
		{
			str = "Speed : ";
			str += std::to_string(PistonEntity->GetSpeed());
			str += ", Lenght : ";
			str += std::to_string(PistonEntity->GetMoveLenght());
			str += ", Offset : ";
			str += std::to_string(PistonEntity->GetMoveLenghtOffset());
			str += ", Dir : ";
			str += std::to_string(PistonEntity->GetEntityDefualtDir().X);
			str += ", ";
			str += std::to_string(PistonEntity->GetEntityDefualtDir().Y);
			UEngineDebug::CoreOutputString(str);
		}
	}
}

void ATileMapEditorMode::ResetAdjustmentEntity()
{
	CurAdjustmentEntity = nullptr;
	CurAdjustmentEntityIndex = -1;
}

void ATileMapEditorMode::CreateEntity()
{
	AEntity* NewEntity = nullptr;

	switch (CurEntityType)
	{
	case EEntityType::Guy:
	case EEntityType::CheckPoint:
	case EEntityType::Teleport:
		NewEntity = GetWorld()->SpawnActor<AEntity>();
		break;
	case EEntityType::Enermy:
	case EEntityType::Platform:
	case EEntityType::PlatformHide:
	case EEntityType::FlipLine:
		NewEntity = GetWorld()->SpawnActor<APistonEntity>();
		break;
	}

	if (NewEntity == nullptr)
		MSGASSERT(nullptr, "Entity Type Unknown.");

	RoomEntityData Data = {};
	Data.Name = CurSelectEntity->GetCurSpriteName();
	Data.EntityType = CurEntityType;
	Data.DefualtDir = FVector2D::RIGHT;
	Data.DefualtLocation = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half();
	NewEntity->SetEntity(Data);
	NewEntity->SetRoom(GameWorld->GetRoom());
	CurAdjustmentEntity = NewEntity;
	GameWorld->GetRoom()->Entites.push_back(NewEntity);
	CurAdjustmentEntityIndex = static_cast<int>(GameWorld->GetRoom()->Entites.size() - 1);
}

void ATileMapEditorMode::DeleteEntity()
{
	if (CurAdjustmentEntity == nullptr)
		return;

	CurAdjustmentEntity->Destroy();
	GameWorld->GetRoom()->Entites.erase(GameWorld->GetRoom()->Entites.begin() + CurAdjustmentEntityIndex);

	--CurAdjustmentEntityIndex;
	if (CurAdjustmentEntityIndex == -1)
		CurAdjustmentEntity = nullptr;
	else
		CurAdjustmentEntity = GameWorld->GetRoom()->Entites[CurAdjustmentEntityIndex];
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

void ATileMapEditorMode::AddEntityLocation(const FVector2D& _AddPos)
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

void ATileMapEditorMode::AddEntityDir(const FVector2D& _Dir)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->AddDir(_Dir);
}

void ATileMapEditorMode::SetEntityDir(const FVector2D& _Dir)
{
	APistonEntity* Enermy = dynamic_cast<APistonEntity*>(CurAdjustmentEntity);

	if (Enermy == nullptr)
		return;

	Enermy->SetDir(_Dir);
}