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

	if (Flip == false)
		MoveValue.Y += GravitySpeed * GET_DELTA;
	else
		MoveValue.Y -= GravitySpeed * GET_DELTA;

	if (UEngineInput::GetInst().IsPress('A'))
		MoveValue.X += FVector2D::LEFT.X * Speed * GET_DELTA;
	if (UEngineInput::GetInst().IsPress('D'))
		MoveValue.X += FVector2D::RIGHT.X * Speed * GET_DELTA;
















	FVector2D NextLocation = GetActorLocation() + MoveValue;
	

	AddActorLocation(MoveValue);






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

	str = "Flip : ";
	if (Flip)
		str += "true";
	else
		str += "false";
	str += ", OnGround : ";
	if (OnGround)
		str += "true";
	else
		str += "false";
	UEngineDebug::CoreOutputString(str);
}