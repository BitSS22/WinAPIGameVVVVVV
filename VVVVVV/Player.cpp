#include "pch.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "Room.h"

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	USpriteRenderer* SpriteRenderer = GetRenderer();
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Guys:: Cyan Right", 0);
	SpriteRenderer->SetSpriteScale(1.f, 0);
	SpriteRenderer->SetOrder(ERenderOrder::PLAYER);

	for (int i = 0; i < static_cast<int>(PixelPoint::LAST); ++i)
		OnTilePoint[i] = GetWorld()->SpawnActor<AActor>();

	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	SetActorScale(SpriteRenderer->GetComponentScale());

	UEngineDebug::SetIsDebug(true);
}

void APlayer::Tick()
{
	Super::Tick();

	FTransform Trans = GetActorTransform();
	if (Flip == false)
	{
		OnTilePoint[static_cast<int>(PixelPoint::LeftBottom)]->SetActorLocation(Trans.CenterLeftBottom());
		OnTilePoint[static_cast<int>(PixelPoint::RightBottom)]->SetActorLocation(Trans.CenterRightBottom());
	}
	else
	{
		OnTilePoint[static_cast<int>(PixelPoint::LeftBottom)]->SetActorLocation(Trans.CenterLeftTop());
		OnTilePoint[static_cast<int>(PixelPoint::RightBottom)]->SetActorLocation(Trans.CenterRightTop());
	}

	if (KEY_DOWN(VK_SPACE) && OnGround == true)
	{
		Flip = !Flip;
		OnGround = false;
	}

	FVector2D MoveValue = FVector2D::ZERO;
	if (OnGround == false)
	{
		if (Flip == false)
			MoveValue.Y += GravitySpeed * GET_DELTA;
		else
			MoveValue.Y -= GravitySpeed * GET_DELTA;
	}

	if (UEngineInput::GetInst().IsPress('A'))
		MoveValue.X += FVector2D::LEFT.X * Speed * GET_DELTA;
	if (UEngineInput::GetInst().IsPress('D'))
		MoveValue.X += FVector2D::RIGHT.X * Speed * GET_DELTA;


	for (int i = 0; i < static_cast<int>(PixelPoint::LAST); ++i)
	{
		FVector2D NextPointPos = OnTilePoint[i]->GetActorLocation() + MoveValue;
		FIntPoint NextPointTileIndex = GetRoom()->GetOnTileIndex(NextPointPos);
		string NextPointTileName = GetRoom()->GetTileName(NextPointTileIndex);

		if (NextPointTileName.find("COLLISIONTILES::") != std::string::npos && OnGround == false)
		{
			OnGround = true;
			if (Flip == false)
				MoveValue = FVector2D(MoveValue.X, NextPointPos.Y - (GetActorLocation() + NextPointPos).Y);
			else
				MoveValue = FVector2D(MoveValue.X, -(NextPointPos.Y - (GetActorLocation() + NextPointPos).Y));
		}
	}

	AddActorLocation(MoveValue);

	


	

	// ¹æ ÀÌµ¿
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FIntPoint CurRoomIndex = GetRoom()->GetGameWorld()->GetCurRoomIndex();

	if (GetActorLocation().X < 0)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X - 1, CurRoomIndex.Y });
		AddActorLocation({ WindowSize.X, 0.f });
	}
	else if (GetActorLocation().X > WindowSize.X)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X + 1, CurRoomIndex.Y });
		AddActorLocation({ -WindowSize.X, 0.f });
	}
	else if (GetActorLocation().Y < 0)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X, CurRoomIndex.Y - 1 });
		AddActorLocation({ 0.f, WindowSize.Y });
	}
	else if (GetActorLocation().Y > WindowSize.Y)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X, CurRoomIndex.Y + 1 });
		AddActorLocation({ 0.f, -WindowSize.Y });
	}

	//DEBUG
	for (int i = 0; i < static_cast<int>(PixelPoint::LAST); ++i)
		UEngineDebug::CoreDebugRender(FTransform(OnTilePoint[i]->GetActorLocation(), FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);

}