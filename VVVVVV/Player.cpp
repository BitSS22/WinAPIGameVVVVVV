#include "pch.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "GameWorld.h"
#include "Room.h"
#include "PistonEntity.h"

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

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

	// Create FSM
	FSM.CreateState(EPlayerState::Idle, bind(&APlayer::Idle, this));
	FSM.CreateState(EPlayerState::Move, bind(&APlayer::Move, this));
	FSM.CreateState(EPlayerState::Death, bind(&APlayer::Death, this));

	FSM.ChangeState(EPlayerState::Idle);

	// Debug
	UEngineDebug::SetIsDebug(true);
}

void APlayer::Tick()
{
	Super::Tick();

	FSM.Update();

	//DEBUG
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

void APlayer::Idle()
{
	SetAnimation();
	Gravity();
	FlipCheck();
	TileCheck();
	KeyCheck();
	MoveRoomCheck();
	DeathCheck();
	Reset();

	AddActorLocation(MoveValue);
	MoveValue = FVector2D::ZERO;

	if (IsDeath == true)
		FSM.ChangeState(EPlayerState::Death);

	if ((KEY_PRESS(VK_LEFT) || KEY_PRESS(VK_RIGHT)))
		FSM.ChangeState(EPlayerState::Move);
}

void APlayer::Move()
{
	SetAnimation();
	Gravity();
	FlipCheck();
	TileCheck();
	KeyCheck();
	MoveRoomCheck();
	DeathCheck();
	Reset();

	AddActorLocation(MoveValue);
	MoveValue = FVector2D::ZERO;

	if (KEY_FREE(VK_LEFT) && KEY_FREE(VK_RIGHT))
		FSM.ChangeState(EPlayerState::Idle);
}

void APlayer::Death()
{
	CurDeathTime += GET_DELTA;

	if (CurDeathTime >= DeathTime)
	{
		CurDeathTime = 0.f;
		IsDeath = false;
		FSM.ChangeState(EPlayerState::Idle);
	}
}

void APlayer::SetAnimation()
{
	AnimationName.clear();

	if (KEY_PRESS(VK_LEFT))
	{
		AnimationName += "Move ";
		LastDir = FVector2D::LEFT;
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		AnimationName += "Move ";
		LastDir = FVector2D::RIGHT;
	}
	else
		AnimationName += "Idle ";

	if (IsSad == true)
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
	if (OnGround == true)
		return;

	if (IsFlip == false)
		MoveValue.Y += GravityForce * GET_DELTA;
	else
		MoveValue.Y -= GravityForce * GET_DELTA;
}

void APlayer::FlipCheck()
{
	if (KEY_DOWN(VK_SPACE))
	{
		IsFlip = !IsFlip;
		OnGround = false;
	}
}

void APlayer::TileCheck()
{
}

void APlayer::KeyCheck()
{
	if (KEY_PRESS(VK_LEFT))
		MoveValue += FVector2D::LEFT * Speed * GET_DELTA;
	else if (KEY_PRESS(VK_RIGHT))
		MoveValue += FVector2D::RIGHT * Speed * GET_DELTA;
}

void APlayer::MoveRoomCheck()
{
	FTransform Transform = GetActorTransform();
	FVector2D OutDir = ARoom::IsOutScreen(Transform);

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
}

void APlayer::Reset()
{
}
