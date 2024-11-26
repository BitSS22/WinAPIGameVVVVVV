#include "pch.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "GameWorld.h"
#include "Room.h"
#include "PistonEntity.h"
#include "Tile.h"
#include <conio.h>

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayerDefualtSetup();

	// Debug
	//UEngineDebug::SetIsDebug(true);
}

void APlayer::Tick()
{
	Super::Tick();


	// Test Code
	if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT) && KEY_PRESS(VK_MENU) && KEY_DOWN('1'))
		TestTrigger = !TestTrigger;

	TestPrevCount = GetTickCount();

	while (TestTrigger == true)
	{
		TestCount = GetTickCount();

		if (TestCount >= 200 + TestPrevCount)
		{
			break;
		}
	}

	ResetData();

	if (IsDeath == true)
		Death();
	else
	{
		Input();
		Gravity();
		MoveRoomCheck();
		EntityCollisionCheck();
		TileCheck();
		Move();
		DeathCheck();
		AnimationChange();
	}

	if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT) && KEY_PRESS(VK_MENU) && KEY_DOWN(VK_SPACE) && POWEROVERWHELMING == false)
	{
		POWEROVERWHELMING = true;
		UEngineSound::Play("coin.wav");
	}

	if (KEY_DOWN(VK_ESCAPE) && POWEROVERWHELMING == true)
	{
		POWEROVERWHELMING = false;
		UEngineSound::Play("crash.wav");
	}
	//DEBUG
	Debug();
}

void APlayer::LevelChangeStart()
{
	SaveWorldIndex = EGameConst::DefualtSaveRoomIndex;
	SaveLocation = EGameConst::DefualtSaveLocation;
	SaveFlip = false;
	ReSpawn();
}

void APlayer::Input()
{
	if (KEY_PRESS(VK_LEFT))
	{
		MoveValue += FVector2D::LEFT * Speed * GET_DELTA;
		LastDir = FVector2D::LEFT;
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		MoveValue += FVector2D::RIGHT * Speed * GET_DELTA;
		LastDir = FVector2D::RIGHT;
	}

	if (KEY_DOWN(VK_SPACE) && IsGround == true && IsDeath == false)
		SetFlip(!IsFlip);
}

void APlayer::AnimationChange()
{
	if (IsDeath == true || IsGround == false || (KEY_FREE(VK_LEFT) && KEY_FREE(VK_RIGHT)))
		AnimationName += "Idle ";
	else
		AnimationName += "Move ";

	if (IsSad == true || IsDeath == true)
		AnimationName += "Sad";
	
	if (LastDir == FVector2D::LEFT)
		AnimationName += "Left";
	else if (LastDir == FVector2D::RIGHT)
		AnimationName += "Right";

	if (IsFlip == true)
		AnimationName += "Flip";

	Sprite->ChangeAnimation(AnimationName, false);
}

void APlayer::Gravity()
{
	if (IsFlip == false)
		MoveValue.Y += GravityForce * GET_DELTA;
	else
		MoveValue.Y -= GravityForce * GET_DELTA;

	SetGround(false);
}

void APlayer::Death()
{
	CurDeathTime += GET_DELTA;

	if (CurDeathTime >= DeathTime)
	{
		CurDeathTime = 0.f;
		SetDeath(false);
		ReSpawn();
	}
}

void APlayer::EntityCollisionCheck()
{
	const vector<AEntity*>& Entites = AGameWorld::GetRoom()->GetEntitesCRef();

	APistonEntity::SetFlipLineCollisionStay(false);

	for (size_t i = 0; i < Entites.size(); ++i)
	{
		if (Entites[i]->IsActive() == false)
			continue;
		Entites[i]->Collision(this);
	}

	if (APistonEntity::GetFlipLineCollisionStay() == false)
		APistonEntity::SetIsCollisionFlipLine(false);
}

void APlayer::TileCheck()
{
	// Player Up, Down CollisionTile Check
	bool CollisionTopBottom = false;
	bool RailLeft = false;
	bool RailRight = false;

	FVector2D(*Line)[APlayer::PointCount] = nullptr;

	if (IsFlip == false)
		Line = &Points[static_cast<int>(EPlayerPoint::Bottom)];
	else
		Line = &Points[static_cast<int>(EPlayerPoint::Top)];

	for (int i = 0; i < APlayer::PointCount; ++i)
	{
		FVector2D PlayerPoint = GetActorLocation() + (*Line)[i];
		FVector2D PlayerNextPoint = FVector2D(PlayerPoint.X, PlayerPoint.Y + MoveValue.Y);
		FIntPoint TileIndex = AGameWorld::GetRoom()->GetOnTileIndex(PlayerNextPoint);
		ETileType TileType = AGameWorld::GetRoom()->GetTileType(TileIndex);

		switch (TileType)
		{
		case ETileType::Collision:
		case ETileType::Animation:
			CollisionTopBottom = true;
			break;
		case ETileType::RailLeft:
			CollisionTopBottom = true;
			RailLeft = true;
			break;
		case ETileType::RailRight:
			CollisionTopBottom = true;
			RailRight = true;
			break;
		}
	}

	if (CollisionTopBottom == true)
	{
		if (IsFlip == false)
		{
			if (RailLeft == true)
				MoveValue.X -= EGameConst::RailSpeed * GET_DELTA;
			if (RailRight == true)
				MoveValue.X += EGameConst::RailSpeed * GET_DELTA;

			float PlayerLine = GetActorTransform().CenterBottom();
			float PlayerNextLine = PlayerLine + MoveValue.Y;
			int TileIndexYLine = AGameWorld::GetRoom()->GetOnTileYIndex(PlayerNextLine);
			float TileYLine = AGameWorld::GetRoom()->GetTileTopLine(TileIndexYLine);

			SetActorLocation(FVector2D(GetActorLocation().X, TileYLine - GetActorScale().HalfY()));
			SetGround(true);
		}
		else
		{
			if (RailLeft == true)
				MoveValue.X -= EGameConst::RailSpeed * GET_DELTA;
			if (RailRight == true)
				MoveValue.X += EGameConst::RailSpeed * GET_DELTA;

			float PlayerLine = GetActorTransform().CenterTop();
			float PlayerNextLine = PlayerLine + MoveValue.Y;
			int TileIndexYLine = AGameWorld::GetRoom()->GetOnTileYIndex(PlayerNextLine);
			float TileYLine = AGameWorld::GetRoom()->GetTileBottomLine(TileIndexYLine);

			SetActorLocation(FVector2D(GetActorLocation().X, TileYLine + GetActorScale().HalfY()));
			SetGround(true);
		}
	}

	// Player Left, Right CollisionTile Check
	bool CollisionLeft = false;

	for (int i = 0; i < APlayer::PointCount; ++i)
	{
		FVector2D PlayerPoint = GetActorLocation() + Points[static_cast<int>(EPlayerPoint::Left)][i];
		FVector2D PlayerNextPoint = FVector2D(PlayerPoint.X + MoveValue.X, PlayerPoint.Y);
		FIntPoint TileIndex = AGameWorld::GetRoom()->GetOnTileIndex(PlayerNextPoint);
		ETileType TileType = AGameWorld::GetRoom()->GetTileType(TileIndex);

		switch (TileType)
		{
		case ETileType::Collision:
		case ETileType::Animation:
		case ETileType::RailLeft:
		case ETileType::RailRight:
			CollisionLeft = true;
			break;
		}
	}

	if (CollisionLeft == true)
	{
		float PlayerLine = GetActorTransform().CenterLeft();
		float PlayerNextLine = PlayerLine + MoveValue.X;
		int TileIndexXLine = AGameWorld::GetRoom()->GetOnTileXIndex(PlayerNextLine);
		float TileXLine = AGameWorld::GetRoom()->GetTileRightLine(TileIndexXLine);

		SetActorLocation(FVector2D(TileXLine + GetActorScale().HalfX(), GetActorLocation().Y));
		MoveValue.X = 0.f;
	}

	bool CollisionRight = false;

	for (int i = 0; i < APlayer::PointCount; ++i)
	{
		FVector2D PlayerPoint = GetActorLocation() + Points[static_cast<int>(EPlayerPoint::Right)][i];
		FVector2D PlayerNextPoint = FVector2D(PlayerPoint.X + MoveValue.X, PlayerPoint.Y);
		FIntPoint TileIndex = AGameWorld::GetRoom()->GetOnTileIndex(PlayerNextPoint);
		ETileType TileType = AGameWorld::GetRoom()->GetTileType(TileIndex);

		switch (TileType)
		{
		case ETileType::Collision:
		case ETileType::Animation:
		case ETileType::RailLeft:
		case ETileType::RailRight:
			CollisionRight = true;
			break;
		}
	}

	if (CollisionRight == true)
	{
		float PlayerLine = GetActorTransform().CenterRight();
		float PlayerNextLine = PlayerLine + MoveValue.X;
		int TileIndexXLine = AGameWorld::GetRoom()->GetOnTileXIndex(PlayerNextLine);
		float TileXLine = AGameWorld::GetRoom()->GetTileLeftLine(TileIndexXLine);

		SetActorLocation(FVector2D(TileXLine - GetActorScale().HalfX(), GetActorLocation().Y));
		MoveValue.X = 0.f;
	}
}

void APlayer::MoveRoomCheck()
{
	FTransform Transform = GetActorTransform();
	Transform.Scale = Transform.Scale.Half();
	FVector2D OutDir = AGameWorld::GetRoom()->IsOutScreen(Transform);

	if (OutDir == FVector2D::ZERO)
		return;

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FIntPoint CurRoomIndex = AGameWorld::GetCurRoomIndex();
	FVector2D MoveLen = WindowSize + Transform.Scale;
	MoveLen.X *= -OutDir.X;
	MoveLen.Y *= -OutDir.Y;
	AddActorLocation(MoveLen);

	if (AGameWorld::GetRoom()->GetIsLoop() == true)
	{
		FIntPoint Index = AGameWorld::GetRoom()->GetOnTileIndex(GetActorLocation());
		if (Index.X < 0)
			Index.X = 0;
		if (Index.X >= EGameConst::TileCount.X)
			Index.X = EGameConst::TileCount.X - 1;
		if (Index.Y < 0)
			Index.Y = 0;
		if (Index.Y >= EGameConst::TileCount.Y)
			Index.Y = EGameConst::TileCount.Y - 1;

		ETileType OppositeTileType = AGameWorld::GetRoom()->GetTileType(Index);
		if (OppositeTileType != ETileType::None)
			AGameWorld::GetRoom()->MoveRoom(CurRoomIndex + OutDir);
	}
	else
		AGameWorld::GetRoom()->MoveRoom(CurRoomIndex + OutDir);
}

void APlayer::DeathCheck()
{
	for (int i = 0; i < static_cast<int>(EPlayerPoint::Last); ++i)
	{
		for (int j = 0; j < APlayer::PointCount; ++j)
		{
			FVector2D Location = GetActorLocation() + Points[i][j];
			ETileType Type = AGameWorld::GetRoom()->GetTileType(Location);

			if (Type == ETileType::Spike)
			{
				SetDeath(true);
				return;
			}
		}
	}
}

void APlayer::Move()
{
	if (IsGround == true)
		MoveValue.Y = 0.f;

	AddActorLocation(MoveValue);
}

void APlayer::ResetData()
{
	AnimationName.clear();
	MoveValue = FVector2D::ZERO;
}

void APlayer::PlayerDefualtSetup()
{
	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Guys:: Cyan Right", 0);
	Sprite->SetSpriteScale(1.f, 0);
	Sprite->SetOrder(ERenderOrder::PLAYER);

	Sprite->CreateAnimation("Move Left", "Guys:: Cyan Left", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Move Right", "Guys:: Cyan Right", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Move LeftFlip", "Guys:: Cyan rLeft", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Move RightFlip", "Guys:: Cyan rRight", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle Left", "Guys:: Cyan Left", 0, 0, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle Right", "Guys:: Cyan Right", 0, 0, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle LeftFlip", "Guys:: Cyan rLeft", 0, 0, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle RightFlip", "Guys:: Cyan rRight", 0, 0, EGameConst::AnimationTime, true);

	Sprite->CreateAnimation("Move SadLeft", "Guys:: Cyan Sad Left", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Move SadRight", "Guys:: Cyan Sad Right", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Move SadLeftFlip", "Guys:: Cyan Sad rLeft", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Move SadRightFlip", "Guys:: Cyan Sad rRight", 0, 1, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle SadLeft", "Guys:: Cyan Sad Left", 0, 0, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle SadRight", "Guys:: Cyan Sad Right", 0, 0, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle SadLeftFlip", "Guys:: Cyan Sad rLeft", 0, 0, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("Idle SadRightFlip", "Guys:: Cyan Sad rRight", 0, 0, EGameConst::AnimationTime, true);

	SetActorLocation(FVector2D(320.f, 350.f));
	SetActorScale(Sprite->GetComponentScale());

	// PixelPointInit
	FVector2D StartPoint = GetActorScale();
	StartPoint.X = -StartPoint.HalfX() + 1.f;
	StartPoint.Y = -StartPoint.HalfY() + 1.f;

	for (int i = 0; i < PointCount; ++i)
	{
		float OffsetX = (GetActorScale().X - 2.f) / (PointCount - 1);
		float OffsetY = (GetActorScale().Y - 2.f) / (PointCount - 1);

		Points[static_cast<int>(EPlayerPoint::Left)][i] = FVector2D(-GetActorScale().HalfX(), StartPoint.Y + OffsetY * i);
		Points[static_cast<int>(EPlayerPoint::Right)][i] = FVector2D(GetActorScale().HalfX(), StartPoint.Y + OffsetY * i);
		Points[static_cast<int>(EPlayerPoint::Top)][i] = FVector2D(StartPoint.X + OffsetX * i, -GetActorScale().HalfY());
		Points[static_cast<int>(EPlayerPoint::Bottom)][i] = FVector2D(StartPoint.X + OffsetX * i, GetActorScale().HalfY());
	}
}

void APlayer::Debug()
{
	if (KEY_DOWN(VK_F1))
		UEngineDebug::SwitchIsDebug();

	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);
	string str = "Location : ";
	str += std::to_string(GetActorLocation().X);
	str += ",";
	str += std::to_string(GetActorLocation().Y);
	UEngineDebug::CoreOutputString(str);

	str = "Left:";
	str += std::to_string(GetActorTransform().CenterLeft());
	str += " Right:";
	str += std::to_string(GetActorTransform().CenterRight());
	str += " Top:";
	str += std::to_string(GetActorTransform().CenterTop());
	str += " Bottom:";
	str += std::to_string(GetActorTransform().CenterBottom());
	UEngineDebug::CoreOutputString(str);

	str = "Ground : ";
	if (IsGround == true)
		str += "true";
	else
		str += "false";
	str += ", MoveValue : ";
	str += std::to_string(MoveValue.X);
	str += ",";
	str += std::to_string(MoveValue.Y);
	UEngineDebug::CoreOutputString(str);


	str = "World Index : ";
	str += std::to_string(AGameWorld::GetCurRoomIndex().X);
	str += ",";
	str += std::to_string(AGameWorld::GetCurRoomIndex().Y);
	UEngineDebug::CoreOutputString(str);
}

void APlayer::ReSpawn()
{
	if (AGameWorld::GetCurRoomIndex() != SaveWorldIndex)
		AGameWorld::GetRoom()->MoveRoom(SaveWorldIndex);
	SetActorLocation(SaveLocation);
	IsFlip = SaveFlip;
}
