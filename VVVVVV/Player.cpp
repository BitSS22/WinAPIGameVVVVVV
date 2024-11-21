#include "pch.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "GameWorld.h"
#include "Room.h"
#include "PistonEntity.h"
#include "Tile.h"

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
	UEngineDebug::SetIsDebug(true);
}

void APlayer::Tick()
{
	Super::Tick();


	if (IsDeath == true)
	{
		Death();
	}
	else
	{
		Input();
		Gravity();
		MoveRoomCheck();
		EntityCollisionCheck();
		TileCheck();
		AddActorLocation(MoveValue);
		DeathCheck();
		if (KEY_DOWN('A'))
			SetDeath(true);
		AnimationChange();
	}

	ResetData();

	//DEBUG
	Debug();
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
	{
		IsFlip = !IsFlip;
		IsGround = false;
	}
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
}

void APlayer::TileCheck()
{
	// Player Up, Down CollisionTile Check
	bool CollisionTopBottm = false;
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
			CollisionTopBottm = true;
			break;
		case ETileType::RailLeft:
			CollisionTopBottm = true;
			RailLeft = true;
			break;
		case ETileType::RailRight:
			CollisionTopBottm = true;
			RailRight = true;
			break;
		}
	}

	if (CollisionTopBottm == true)
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
			MoveValue.Y = 0.f;
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
			MoveValue.Y = 0.f;
		}

		SetGround(true);
	}
	else
		SetGround(false);



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
	AGameWorld::GetRoom()->MoveRoom(CurRoomIndex + OutDir);
	FVector2D MoveLen = WindowSize + Transform.Scale;
	MoveLen.X *= OutDir.X;
	MoveLen.Y *= OutDir.Y;
	AddActorLocation(-MoveLen);
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

	Collider = CreateDefaultSubObject<U2DCollision>();
	Collider->SetCollisionGroup(ECollisionGroup::Player);
	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetComponentScale(Sprite->GetComponentScale());

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
}
