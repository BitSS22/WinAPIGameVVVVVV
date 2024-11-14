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

	FVector2D MoveValue = FVector2D::ZERO;

	if (OnGround == false)
	{
		if (Flip == false)
			MoveValue.Y += GravitySpeed;
		else
			MoveValue.Y -= GravitySpeed;
	}

	if (UEngineInput::GetInst().IsPress('A'))
		MoveValue.X += FVector2D::LEFT.X * Speed;
	if (UEngineInput::GetInst().IsPress('D'))
		MoveValue.X += FVector2D::RIGHT.X * Speed;

	FVector2D NextLocation = GetActorLocation() + MoveValue * GET_DELTA;
	FVector2D TileIndex = GetRoom()->GetOnTileIndex(NextLocation);
	string NextTileName = GetRoom()->GetTileName(TileIndex);

	if (NextTileName.find("COLLISIONTILES::") != std::string::npos && OnGround == false)
	{
		if (Flip == false)
		{
			float PosY = (TileIndex.Y) * GetRoom()->GetTileScale().Y;
			PosY -= GetActorScale().HalfY();
			SetActorLocation({ GetActorLocation().X, PosY });
		}
		else
		{
			float PosY = (TileIndex.Y + 1) * GetRoom()->GetTileScale().Y;
			PosY += GetActorScale().HalfY();
			SetActorLocation({ GetActorLocation().X, PosY });
		}

		MoveValue.Y = 0.f;
		OnGround = true;
	}
		
	AddActorLocation(MoveValue * GET_DELTA);

	


	

	// Move Room
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
	if (KEY_DOWN(VK_F1))
		UEngineDebug::SwitchIsDebug();

	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);
	string str = "Location : ";
	str += std::to_string(GetActorLocation().X);
	str += ",";
	str += std::to_string(GetActorLocation().Y);
	UEngineDebug::CoreOutputString(str);
}