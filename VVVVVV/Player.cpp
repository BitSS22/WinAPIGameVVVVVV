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

	// Key Input Check
	Input();

	// Animation Change
	AnimationChange();

	// Add Gravity
	Gravity();

	// Entity
	EntityCollisionCheck();

	// Tile Collision Check
	TileCheck();

	// Death Check
	if (IsDeath == true)
		Death();
	else
	{
		// Move
		AddActorLocation(MoveValue);
		MoveRoomCheck();
	}

	// Reset Data
	ResetData();

	//DEBUG
	Debug();
}

void APlayer::Input()
{
	if (KEY_PRESS(VK_LEFT) && IsDeath == false)
	{
		MoveValue += FVector2D::LEFT * Speed * GET_DELTA;
		AnimationName += "Move ";
		LastDir = FVector2D::LEFT;
	}
	else if (KEY_PRESS(VK_RIGHT) && IsDeath == false)
	{
		MoveValue += FVector2D::RIGHT * Speed * GET_DELTA;
		AnimationName += "Move ";
		LastDir = FVector2D::RIGHT;
	}
	else
		AnimationName += "Idle ";

	if (KEY_DOWN(VK_SPACE) && IsGround == true && IsDeath == false)
	{
		IsFlip = !IsFlip;
		IsGround = false;
	}
}

void APlayer::AnimationChange()
{
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
	if (IsGround == false)
	{
		if (IsFlip == false)
			MoveValue.Y += GravityForce * GET_DELTA;
		else
			MoveValue.Y -= GravityForce * GET_DELTA;
	}
}

void APlayer::Death()
{
	CurDeathTime += GET_DELTA;

	if (CurDeathTime >= DeathTime)
	{
		CurDeathTime = 0.f;
		IsDeath = false;
		ReSpawn();
	}
}

void APlayer::EntityCollisionCheck()
{
}

void APlayer::TileCheck()
{
	FVector2D Location = GetActorLocation() + Points[static_cast<int>(EPlayerPoint::Bottom)][2];
	FIntPoint Index = AGameWorld::GetRoom()->GetOnTileIndex(Location);
	const ATile* Tile = AGameWorld::GetRoom()->GetTile(Index);

	if (Tile == nullptr)
		return;

	if (Tile->GetType() == ETileType::RailLeft)
		Tile->TileCollision(this, MoveValue);
	else if (Tile->GetType() == ETileType::RailRight)
		Tile->TileCollision(this, MoveValue);
	else if (Tile->GetType() == ETileType::Collision)
		Tile->TileCollision(this, MoveValue);
	else if (Tile->GetType() == ETileType::Animation)
		Tile->TileCollision(this, MoveValue);
	else if (Tile->GetType() == ETileType::Spike)
		Tile->TileCollision(this, MoveValue);
	
	// TODO. Tile Collision Code Create
	APlayer* Player = dynamic_cast<APlayer*>(_Actor);

	switch (TileType)
	{
	case ETileType::Collision:
		Push(_Actor, _MoveValue);
		if (Player != nullptr)
			Player->SetGround(true);
		break;
	case ETileType::Spike:
	{
		if (Player != nullptr)
			Player->SetDeath(true);
	}
	break;
	case ETileType::Animation:
		Push(_Actor, _MoveValue);
		if (Player != nullptr)
			Player->SetGround(true);
		break;
	case ETileType::RailLeft:
		_MoveValue.X -= EGameConst::RailSpeed * GET_DELTA;
		Push(_Actor, _MoveValue);
		if (Player != nullptr)
			Player->SetGround(true);
		break;
	case ETileType::RailRight:
		_MoveValue.X += EGameConst::RailSpeed * GET_DELTA;
		Push(_Actor, _MoveValue);
		if (Player != nullptr)
			Player->SetGround(true);
		break;
	}

	FTransform ActorTransform = _Actor->GetActorTransform();
	FTransform ActorNextTransform = FTransform(ActorTransform.Location + _MoveValue, ActorTransform.Scale);
	FTransform Transform = GetActorTransform();
	FVector2D PushDir = ActorTransform.Location - ActorNextTransform.Location;

	FVector2D Offset = FVector2D::ZERO;
	if (PushDir.X < 0.f)
		Offset.X = Transform.CenterLeft() - ActorNextTransform.CenterRight() + 1.f;
	else if (PushDir.X > 0.f)
		Offset.X = Transform.CenterRight() - ActorNextTransform.CenterLeft() - 1.f;

	if (PushDir.Y < 0.f)
		Offset.Y = Transform.CenterTop() - ActorNextTransform.CenterBottom() - 1.f;
	else if (PushDir.Y > 0.f)
		Offset.Y = Transform.CenterBottom() - ActorNextTransform.CenterTop() + 1.f;

	//if (abs(Offset.X) > abs(Offset.Y))
	//	Offset.X = 0.f;
	//else
	//	Offset.Y = 0.f;

	_MoveValue += Offset;
}

void APlayer::MoveRoomCheck()
{
	FTransform Transform = GetActorTransform();
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
		FVector2D Point = { 0.f, 0.f };
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
	AGameWorld::GetRoom()->MoveRoom(SaveWorldIndex);
	SetActorLocation(SaveLocation);
}
