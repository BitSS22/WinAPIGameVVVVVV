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

	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
	SetActorScale(SpriteRenderer->GetComponentScale());

	UEngineDebug::SetIsDebug(true);
}

void APlayer::Tick()
{
	Super::Tick();
	
	if (KEY_DOWN(VK_SPACE) && OnGround == true)
	{
		Flip = !Flip;
		OnGround = false;
	}

	if (Flip == false)
	{
		Points[static_cast<int>(PixelPoint::LeftBottom)] = GetActorTransform().CenterLeftBottom();
		Points[static_cast<int>(PixelPoint::RightBottom)] = GetActorTransform().CenterRightBottom();
		Points[static_cast<int>(PixelPoint::LeftTop)] = GetActorTransform().CenterLeftTop();
		Points[static_cast<int>(PixelPoint::RightTop)] = GetActorTransform().CenterRightTop();
	}
	else
	{
		Points[static_cast<int>(PixelPoint::LeftBottom)] = GetActorTransform().CenterLeftTop();
		Points[static_cast<int>(PixelPoint::RightBottom)] = GetActorTransform().CenterRightTop();
		Points[static_cast<int>(PixelPoint::LeftTop)] = GetActorTransform().CenterLeftBottom();
		Points[static_cast<int>(PixelPoint::RightTop)] = GetActorTransform().CenterRightBottom();
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

	FVector2D NextLocation = GetActorLocation() + MoveValue;
	FTransform NextTransform = FTransform(NextLocation, GetActorScale());
	
	string NextTileName = GetRoom()->GetTileName(GetRoom()->GetOnTileIndex(Points[static_cast<int>(PixelPoint::LeftBottom)]));
	//string NextCenterLeftBottomTileName = GetRoom()->GetTileName(GetRoom()->GetOnTileIndex(NextTransform.CenterLeftBottom()));
	//string NextCenterLeftBottomTileName = GetRoom()->GetTileName(GetRoom()->GetOnTileIndex(NextTransform.CenterLeftBottom()));
	//string NextCenterLeftBottomTileName = GetRoom()->GetTileName(GetRoom()->GetOnTileIndex(NextTransform.CenterLeftBottom()));

	if (NextTileName.find("NONE TILE") == std::string::npos && OnGround == false)
	{
		FVector2D Location = GetActorLocation();
		FIntPoint TileIndex = GetRoom()->GetOnTileIndex(Points[static_cast<int>(PixelPoint::LeftBottom)]);
		if (Flip == false)
		{
			int GroundLine = (TileIndex.Y + 1) * GetRoom()->GetTileScale().Y;
			SetActorLocation({ GetActorLocation().X, float(GroundLine - GetRoom()->GetTileScale().Y - GetActorScale().HalfY()) });
		}
		else
		{
			int GroundLine = (TileIndex.Y) * GetRoom()->GetTileScale().Y;
			SetActorLocation({ GetActorLocation().X, float(GroundLine + GetRoom()->GetTileScale().Y + GetActorScale().HalfY()) });
		}
		MoveValue.Y = 0.f;
		OnGround = true;
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
	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);

}