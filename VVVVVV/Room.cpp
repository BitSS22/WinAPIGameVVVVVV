#include "pch.h"
#include "Room.h"
#include "BackGround.h"
#include "GameWorld.h"
#include "Entity.h"
#include "PistonEntity.h"
#include "Player.h"
#include "Tile.h"
#include <EnginePlatform/EngineSound.h>

ARoom::ARoom()
{
}

ARoom::~ARoom()
{
}

void ARoom::BeginPlay()
{
	Super::BeginPlay();

	BackGround = GetWorld()->SpawnActor<ABackGround>();

	// 타일 스프라이트
	Tiles.resize(EGameConst::TileCount.Y);
	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		Tiles[y].resize(EGameConst::TileCount.X);
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Tiles[y][x] = GetWorld()->SpawnActor<ATile>();
			Tiles[y][x]->SetActorLocation(FVector2D(EGameConst::TileScale.X * x + EGameConst::TileScale.X / 2.f, EGameConst::TileScale.Y * y + EGameConst::TileScale.Y / 2.f));
		}
	}

	FileLoadInit();
}

void ARoom::Tick()
{
	Super::Tick();

	SoundUpdate();
}

void ARoom::LevelChangeStart()
{
	MoveRoom(EGameConst::DefualtSaveRoomIndex);
}

void ARoom::MoveRoom(FIntPoint _Index)
{
	if (_Index.X < 0)
		_Index.X = EGameConst::WorldMaxIndex.X - 1;
	else if (_Index.X >= EGameConst::WorldMaxIndex.X)
		_Index.X = 0;
	if (_Index.Y < 0)
		_Index.Y = EGameConst::WorldMaxIndex.Y - 1;
	else if (_Index.Y >= EGameConst::WorldMaxIndex.Y)
		_Index.Y = 0;

	SetRoom(_Index);
	AGameWorld::SetCurRoomIndex(_Index);
}

void ARoom::SetRoom(const FIntPoint& _RoomIndex)
{
	SetRoom(AGameWorld::GetRoomDatasRef(_RoomIndex));
}

void ARoom::SetRoom(const RoomData& _Data)
{
	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Tiles[y][x]->SetTile(_Data.TileDatas[y][x]);
		}
	}

	BackGround->SetBackGround(_Data.BackGroundData);
	LoopRoom = _Data.LoopRoom;

	for (size_t i = 0; i < Entites.size(); ++i)
		Entites[i]->Destroy();
	Entites.clear();

	SetBGM(_Data.BGMName);

	for (size_t i = 0; i < _Data.EntityDatas.size(); ++i)
	{
		AEntity* NewEntity = nullptr;

		switch (_Data.EntityDatas[i].EntityType)
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
			MSGASSERT(nullptr, "Spawn Entity Unknown Type.");

		NewEntity->SetEntity(_Data.EntityDatas[i]);
		NewEntity->SetRoom(this);
		Entites.push_back(NewEntity);
	}
}

void ARoom::SoundFadeIn()
{
	Volume = UEngineMath::Clamp(Volume + GET_DELTA * EGameConst::BGMFadeTimeScale, 0.f, 1.f);
	BGM.SetVolume(Volume);
}

void ARoom::SoundFadeOut()
{
	Volume = UEngineMath::Clamp(Volume - GET_DELTA * EGameConst::BGMFadeTimeScale, 0.f, 1.f);
	BGM.SetVolume(Volume);
}

void ARoom::SoundUpdate()
{
	if (BGM.GetCurrentSoundName() == "NONE")
		MSGASSERT(nullptr, "BGM Setting Error.");

	if (BGM.GetCurrentSoundName() == NextBGM)
	{
		NextBGM = "NONE";
	}

	if (BGM.IsEmpty() == true && NextBGM != "NONE")
	{
		if (NextBGM.empty() == false)
		{
			BGM = UEngineSound::Play(NextBGM);
			BGM.Loop();
			BGM.SetVolume(Volume);
		}
		
		NextBGM = "NONE";
	}

	if (NextBGM != "NONE" && BGM.IsEmpty() == false && Volume > 0.f)
	{
		SoundFadeOut();

		if (Volume <= 0.f)
		{
			BGM.Stop();
			if (NextBGM.empty() == true)
				BGM.Clear();
			else
			{
				BGM = UEngineSound::Play(NextBGM);
				BGM.Loop();
				BGM.SetVolume(Volume);
			}
			
			NextBGM = "NONE";
		}
	}
	else if (BGM.IsEmpty() == false && Volume < 1.f && NextBGM == "NONE")
		SoundFadeIn();
}

RoomData ARoom::GetRoomData()
{
	RoomData Data = {};

	Data.BackGroundData = BackGround->GetBackGroundData();
	Data.LoopRoom = LoopRoom;
	if (BGM.IsEmpty() == false)
		Data.BGMName = BGM.GetCurrentSoundName();
	else
		Data.BGMName = "";

	for (int y = 0; y < EGameConst::TileCount.Y; ++y)
	{
		for (int x = 0; x < EGameConst::TileCount.X; ++x)
		{
			Data.TileDatas[y][x] = Tiles[y][x]->GetTileData();
		}
	}
	
	for (size_t i = 0; i < Entites.size(); ++i)
		Data.EntityDatas.push_back(Entites[i]->GetEntityData());

	return Data;
}

const ATile* ARoom::GetTile(const FIntPoint& _Index) const
{
	if (IsOutTileIndex(_Index) == true)
		return nullptr;

	return Tiles[_Index.Y][_Index.X];
}

FIntPoint ARoom::GetOnTileIndex(const FVector2D& _Pos) const
{
	FVector2D Pos = _Pos;

	if (Pos.X < 0.f)
		Pos.X -= EGameConst::TileScale.X;
	if (Pos.Y < 0.f)
		Pos.Y -= EGameConst::TileScale.Y;

	return FIntPoint(Pos.X / EGameConst::TileScale.X, Pos.Y / EGameConst::TileScale.Y);
}

int ARoom::GetOnTileXIndex(float _X) const
{
	float line = _X;

	if (line < 0.f)
		line -= EGameConst::TileScale.X;

	return static_cast<int>(line / EGameConst::TileScale.X);
}

int ARoom::GetOnTileYIndex(float _Y) const
{
	float line = _Y;

	if (line < 0.f)
		line -= EGameConst::TileScale.Y;

	return static_cast<int>(line / EGameConst::TileScale.Y);
}

FTransform ARoom::GetTileTransform(const FIntPoint& _TileIndex) const
{
	FVector2D TileSize = EGameConst::TileScale;
	return FTransform(FVector2D(_TileIndex.X * TileSize.X + TileSize.HalfX(), _TileIndex.Y * TileSize.Y + TileSize.HalfY()), FVector2D(TileSize));
}

float ARoom::GetTileTopLine(int _YIndex)
{
	FVector2D TileSize = EGameConst::TileScale;
	return static_cast<float>(_YIndex) * TileSize.Y;
}

float ARoom::GetTileBottomLine(int _YIndex)
{
	FVector2D TileSize = EGameConst::TileScale;
	return static_cast<float>(_YIndex + 1.f) * TileSize.Y;
}

float ARoom::GetTileLeftLine(int _XIndex)
{
	FVector2D TileSize = EGameConst::TileScale;
	return static_cast<float>(_XIndex) * TileSize.X;
}

float ARoom::GetTileRightLine(int _XIndex)
{
	FVector2D TileSize = EGameConst::TileScale;
	return static_cast<float>(_XIndex + 1.f) * TileSize.X;
}

ETileType ARoom::GetTileType(const FVector2D& _Location) const
{
	return GetTileType(GetOnTileIndex(_Location));
}

ETileType ARoom::GetTileType(const FIntPoint& _Index) const
{
	if (_Index.X < 0 || _Index.X >= EGameConst::TileCount.X || _Index.Y < 0 || _Index.Y >= EGameConst::TileCount.Y)
		return ETileType::None;
	else
		return Tiles[_Index.Y][_Index.X]->GetType();
}

FVector2D ARoom::IsOutScreen(const FTransform& Transform) const
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	if (Transform.Location.X < -Transform.Scale.HalfX())
		return FVector2D::LEFT;
	else if (Transform.Location.X > WindowSize.X + Transform.Scale.HalfX())
		return FVector2D::RIGHT;
	else if (Transform.Location.Y < -Transform.Scale.HalfY())
		return FVector2D::UP;
	else if (Transform.Location.Y > WindowSize.Y + Transform.Scale.HalfY())
		return FVector2D::DOWN;

	return FVector2D::ZERO;
}

FVector2D ARoom::IsOutScreen(const FVector2D& _Location) const
{
	return IsOutScreen(FTransform(_Location, FVector2D::ZERO));
}

bool ARoom::IsOutTileIndex(const FIntPoint& _Index) const
{
	if (_Index.X < 0.f)
		return true;
	else if (_Index.Y < 0.f)
		return true;
	else if (_Index.X >= EGameConst::TileCount.X)
		return true;
	else if (_Index.Y >= EGameConst::TileCount.Y)
		return true;

	return false;
}

void ARoom::FileLoadInit()
{
	FIntPoint CurRoomIndex = AGameWorld::GetCurRoomIndex();
	const RoomData& RoomData = AGameWorld::GetRoomDatasRef(CurRoomIndex);
	LoopRoom = RoomData.LoopRoom;
	const vector<RoomEntityData>& EntityDatas = RoomData.EntityDatas;

	for (size_t i = 0; i < Entites.size(); ++i)
		Entites[i]->Destroy();
	Entites.clear();

	SetBGM(RoomData.BGMName);

	for (size_t i = 0; i < EntityDatas.size(); ++i)
	{
		AEntity* NewEntity = nullptr;

		switch (EntityDatas[i].EntityType)
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
			MSGASSERT(nullptr, "Spawn Entity Unknown Type.");

		NewEntity->SetEntity(EntityDatas[i]);
		NewEntity->SetRoom(this);
		Entites.push_back(NewEntity);
	}
}

void ARoom::SetEntityMove(bool _Value)
{
	for (size_t i = 0; i < Entites.size(); ++i)
		Entites[i]->SetIsMove(_Value);
}

void ARoom::SetBGM(std::string_view _Name)
{
	NextBGM = _Name;
}

