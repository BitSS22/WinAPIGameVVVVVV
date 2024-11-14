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
		PointsY[static_cast<int>(PixelPointY::LeftBottom)] = GetActorTransform().CenterLeftBottom();
		PointsY[static_cast<int>(PixelPointY::Bottom)] = FVector2D(GetActorLocation().X, GetActorLocation().Y + GetActorScale().HalfY());
		PointsY[static_cast<int>(PixelPointY::RightBottom)] = GetActorTransform().CenterRightBottom();
	}
	else
	{
		PointsY[static_cast<int>(PixelPointY::LeftBottom)] = GetActorTransform().CenterLeftTop();
		PointsY[static_cast<int>(PixelPointY::Bottom)] = FVector2D(GetActorLocation().X, GetActorLocation().Y - GetActorScale().HalfY());
		PointsY[static_cast<int>(PixelPointY::RightBottom)] = GetActorTransform().CenterRightTop();
	}

	PointsX[static_cast<int>(PixelPointX::Left1)] = GetActorTransform().CenterLeftBottom();
	PointsX[static_cast<int>(PixelPointX::Left1)].Y -= 1.f;
	PointsX[static_cast<int>(PixelPointX::Left2)] = GetActorTransform().CenterLeftBottom();
	PointsX[static_cast<int>(PixelPointX::Left3)].Y -= 15.f;
	PointsX[static_cast<int>(PixelPointX::Left3)] = GetActorTransform().CenterLeftTop();
	PointsX[static_cast<int>(PixelPointX::Left3)].Y += 15.f;
	PointsX[static_cast<int>(PixelPointX::Left4)] = GetActorTransform().CenterLeftTop();
	PointsX[static_cast<int>(PixelPointX::Left4)].Y += 1.f;

	PointsX[static_cast<int>(PixelPointX::Right1)] = GetActorTransform().CenterRightBottom();
	PointsX[static_cast<int>(PixelPointX::Right1)].Y -= 1.f;
	PointsX[static_cast<int>(PixelPointX::Right2)] = GetActorTransform().CenterRightBottom();
	PointsX[static_cast<int>(PixelPointX::Right3)].Y -= 15.f;
	PointsX[static_cast<int>(PixelPointX::Right3)] = GetActorTransform().CenterRightTop();
	PointsX[static_cast<int>(PixelPointX::Right3)].Y += 15.f;
	PointsX[static_cast<int>(PixelPointX::Right4)] = GetActorTransform().CenterRightTop();
	PointsX[static_cast<int>(PixelPointX::Right4)].Y += 1.f;

	FVector2D MoveValue = FVector2D::ZERO;




	if (UEngineInput::GetInst().IsPress('A'))
		MoveValue.X += FVector2D::LEFT.X * Speed * GET_DELTA;
	if (UEngineInput::GetInst().IsPress('D'))
		MoveValue.X += FVector2D::RIGHT.X * Speed * GET_DELTA;

	int Start = 0;
	int End = 0;
	float Dir = 0.f;

	if (MoveValue.X > 0.f)
	{
		Start = static_cast<int>(PixelPointX::Right1);
		End = static_cast<int>(PixelPointX::LAST);
	}
	else
	{
		Start = static_cast<int>(PixelPointX::Left1);
		End = static_cast<int>(PixelPointX::AND);
	}

	for (int i = Start; i < End; ++i)
	{
		FVector2D NextLocation = PointsX[i] + MoveValue;
		FVector2D TileIndex = GetRoom()->GetOnTileIndex(NextLocation);
		string NextTileName = GetRoom()->GetTileName(TileIndex);

		if (NextTileName.find("COLLISIONTILES::") != std::string::npos)
		{
			if (MoveValue.X > 0.f)
			{
				float PosX = (TileIndex.X) * GetRoom()->GetTileScale().X;
				PosX -= GetActorScale().HalfX();
				SetActorLocation({ PosX - 0.1f, GetActorLocation().Y });
			}
			else
			{
				float PosX = (TileIndex.X + 1) * GetRoom()->GetTileScale().X;
				PosX += GetActorScale().HalfX();
				SetActorLocation({ PosX + 0.1f, GetActorLocation().Y });
			}

			MoveValue.X = 0.f;
			OnGround = true;
			break;
		}
	}



	if (Flip == false)
		MoveValue.Y += GravitySpeed * GET_DELTA;
	else
		MoveValue.Y -= GravitySpeed * GET_DELTA;

	for (int i = 0; i < static_cast<int>(PixelPointY::LAST); ++i)
	{
		FVector2D NextLocation = PointsY[i] + MoveValue;
		FVector2D TileIndex = GetRoom()->GetOnTileIndex(NextLocation);
		string NextTileName = GetRoom()->GetTileName(TileIndex);

		if (NextTileName.find("COLLISIONTILES::") != std::string::npos)
		{
			if (Flip == false)
			{
				float PosY = (TileIndex.Y) * GetRoom()->GetTileScale().Y;
				PosY -= GetActorScale().HalfY();
				SetActorLocation({ GetActorLocation().X, PosY - 0.1f });
			}
			else
			{
				float PosY = (TileIndex.Y + 1) * GetRoom()->GetTileScale().Y;
				PosY += GetActorScale().HalfY();
				SetActorLocation({ GetActorLocation().X, PosY + 0.1f });
			}

			MoveValue.Y = 0.f;
			OnGround = true;
			break;
		}

		OnGround = false;
	}















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
}