#include "pch.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include "Room.h"
#include "MoveEntity.h"

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Guys:: Cyan Right", 0);
	SpriteRenderer->SetSpriteScale(1.f, 0);
	SpriteRenderer->SetOrder(ERenderOrder::PLAYER);

	SetActorLocation(FVector2D(320.f, 350.f));
	SetActorScale(SpriteRenderer->GetComponentScale());

	SpriteRenderer->CreateAnimation("WalkLeft", "Guys:: Cyan Left", 0, 1, 0.15f, true);
	SpriteRenderer->CreateAnimation("WalkRight", "Guys:: Cyan Right", 0, 1, 0.15f, true);
	SpriteRenderer->CreateAnimation("FlipWalkLeft", "Guys:: Cyan rLeft", 0, 1, 0.15f, true);
	SpriteRenderer->CreateAnimation("FlipWalkRight", "Guys:: Cyan rRight", 0, 1, 0.15f, true);
	SpriteRenderer->CreateAnimation("IdleLeft", "Guys:: Cyan Left", 0, 0, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("IdleRight", "Guys:: Cyan Right", 0, 0, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("FlipIdleLeft", "Guys:: Cyan rLeft", 0, 0, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("FlipIdleRight", "Guys:: Cyan rRight", 0, 0, EGameConst::AnimationTime, true);

	SpriteRenderer->CreateAnimation("SadIdleLeft", "Guys:: Cyan Sad Left", 0, 0, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("SadIdleRight", "Guys:: Cyan Sad Right", 0, 0, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("SadFlipIdleLeft", "Guys:: Cyan Sad rLeft", 0, 0, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("SadFlipIdleRight", "Guys:: Cyan Sad rRight", 0, 0, EGameConst::AnimationTime, true);

	Collider = CreateDefaultSubObject<U2DCollision>();
	Collider->SetCollisionGroup(ECollisionGroup::Player);
	Collider->SetCollisionType(ECollisionType::Rect);
	Collider->SetComponentScale(SpriteRenderer->GetComponentScale());

	SaveWorldIndex = GetRoom()->GetGameWorld()->GetCurRoomIndex();
	SaveLocation = GetActorLocation();

	UEngineDebug::SetIsDebug(true);
}

void APlayer::Tick()
{
	Super::Tick();

	MoveValue = FVector2D::ZERO;

	SetCollisionPoint();



	Flip();

	for (int i = 0; i < static_cast<int>(PixelPointY::LeftTop); ++i)
	{
		FIntPoint CurIndex = GetRoom()->GetOnTileIndex(PointsY[i]);

		if (IsFlip == false)
			CurIndex = GetRoom()->GetOnTileIndex({ PointsY[i].X, PointsY[i].Y + 1.f });
		else
			CurIndex = GetRoom()->GetOnTileIndex({ PointsY[i].X, PointsY[i].Y - 1.f });

		if (GetRoom()->GetTileName(CurIndex).find("LEFT") != std::string::npos)
		{
			MoveValue.X -= 300.f * GET_DELTA;
			break;
		}
		else if (GetRoom()->GetTileName(CurIndex).find("RIGHT") != std::string::npos)
		{
			MoveValue.X += 300.f * GET_DELTA;
			break;
		}
	}

	Move();

	if (Collider->CollisionOnce(ECollisionGroup::Enermy))
	{
		IsDeath = true;
		GetRoom()->SetIsEntityMove(false);
	}

	if (AActor* Actor = Collider->CollisionOnce(ECollisionGroup::Save))
	{
		SaveWorldIndex = GetRoom()->GetGameWorld()->GetCurRoomIndex();
		SaveLocation = Actor->GetActorLocation();
	}

	vector<AActor*> Actors = Collider->CollisionAll(ECollisionGroup::Platform, MoveValue);

	//if (Actors.empty() == false)
	//{
	//	for (int i = 0; i < Actors.size(); ++i)
	//	{
	//		FVector2D Point = { 0.f, 0.f };

	//		if (GetActorLocation().X < Actors[i]->GetActorLocation().X)
	//			Point = PointsY[static_cast<int>(PixelPointY::RightBottom)];
	//		else
	//			Point = PointsY[static_cast<int>(PixelPointY::LeftBottom)];


	//		FVector2D Vector = Point - Actors[i]->GetActorLocation();
	//		Vector.X = Vector.X / Actors[i]->GetActorScale().X;
	//		Vector.Y = Vector.Y / Actors[i]->GetActorScale().Y;

	//		AMoveEntity* MoveEntity = dynamic_cast<AMoveEntity*>(Actors[i]);

	//		if (Vector.X > Vector.Y && -Vector.X > Vector.Y && IsFlip == false)
	//		{
	//			SetActorLocation({ GetActorLocation().X,  Actors[i]->GetActorTransform().CenterTop() - GetActorScale().HalfY() });
	//			AddActorLocation(MoveEntity->GetEntityDir() * MoveEntity->GetSpeed() * GET_DELTA);
	//			MoveValue.Y = 0.f;
	//			OnGround = true;
	//		}
	//		if (Vector.X < Vector.Y && -Vector.X < Vector.Y && IsFlip == true)
	//		{
	//			SetActorLocation({ GetActorLocation().X,  Actors[i]->GetActorTransform().CenterBottom() + GetActorScale().HalfY() });
	//			AddActorLocation(MoveEntity->GetEntityDir() * MoveEntity->GetSpeed() * GET_DELTA);
	//			MoveValue.Y = 0.f;
	//			OnGround = true;
	//		}
	//		if (Vector.Y > Vector.X && -Vector.Y > Vector.X && GetActorLocation().X < Actors[i]->GetActorLocation().X)
	//		{
	//			SetActorLocation({ Actors[i]->GetActorTransform().CenterLeft() - GetActorScale().HalfX() - 1.f , GetActorLocation().Y });
	//			MoveValue.X = 0.f;
	//		}
	//		if (Vector.Y < Vector.X && -Vector.Y < Vector.X && GetActorLocation().X > Actors[i]->GetActorLocation().X)
	//		{
	//			SetActorLocation({ Actors[i]->GetActorTransform().CenterRight() + GetActorScale().HalfX() + 1.f , GetActorLocation().Y });
	//			MoveValue.X = 0.f;
	//		}
	//	}

	//}


	if (IsDeath == false)
		AddActorLocation(MoveValue);
	
	MoveRoom();


	

	for (int i = 0; i < static_cast<int>(PixelPointY::LAST); ++i)
	{
		FIntPoint CurIndex = GetRoom()->GetOnTileIndex(PointsY[i]);

		if (GetRoom()->GetTileName(CurIndex).find("SPIKETILES::") != std::string::npos)
		{
			IsDeath = true;
			GetRoom()->SetIsEntityMove(false);
			break;
		}
	}


	


	if (IsDeath == true)
	{
		DeathTime += GET_DELTA;
	}

	if (DeathTime >= 1.f)
	{
		DeathTime = 0.f;
		Reset();
		IsDeath = false;
		GetRoom()->SetIsEntityMove(true);
	}

	if (IsDeath == false)
	{
		string Animation = "";
		if (IsFlip == true)
			Animation += "Flip";
		if (KEY_PRESS(VK_LEFT))
			SpriteRenderer->ChangeAnimation(Animation += "WalkLeft");
		else if (KEY_PRESS(VK_RIGHT))
			SpriteRenderer->ChangeAnimation(Animation += "WalkRight");
		else if (LastKey == FVector2D::LEFT)
			SpriteRenderer->ChangeAnimation(Animation += "IdleLeft");
		else if (LastKey == FVector2D::RIGHT)
			SpriteRenderer->ChangeAnimation(Animation += "IdleRight");
	}
	else
	{
		string Animation = "Sad";
		if (IsFlip == true)
			Animation += "Flip";
		if (LastKey == FVector2D::LEFT)
			SpriteRenderer->ChangeAnimation(Animation += "IdleLeft");
		else if (LastKey == FVector2D::RIGHT)
			SpriteRenderer->ChangeAnimation(Animation += "IdleRight");
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

void APlayer::Move()
{
	if (IsDeath == false)
	{
		if (UEngineInput::GetInst().IsPress(VK_LEFT))
		{
			MoveValue.X += FVector2D::LEFT.X * Speed * GET_DELTA;
			LastKey = FVector2D::LEFT;
		}
		else if (UEngineInput::GetInst().IsPress(VK_RIGHT))
		{
			MoveValue.X += FVector2D::RIGHT.X * Speed * GET_DELTA;
			LastKey = FVector2D::RIGHT;
		}
	}

	int Start = 0;
	int End = 0;

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

		if ((NextTileName.find("COLLISIONTILES::") != std::string::npos) || (NextTileName.find("ANIMATIONTILES::") != std::string::npos) || (NextTileName.find("RAILTILES::") != std::string::npos))
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
			break;
		}
	}
}

void APlayer::Flip()
{
	if (KEY_DOWN(VK_SPACE) && OnGround == true && IsDeath == false)
	{
		IsFlip = !IsFlip;
		OnGround = false;
	}

	if (IsFlip == false)
		MoveValue.Y += GravitySpeed * GET_DELTA;
	else
		MoveValue.Y -= GravitySpeed * GET_DELTA;

	for (int i = 0; i < static_cast<int>(PixelPointY::LeftTop); ++i)
	{
		FVector2D NextLocation = PointsY[i] + MoveValue;
		FVector2D TileIndex = GetRoom()->GetOnTileIndex(NextLocation);
		string NextTileName = GetRoom()->GetTileName(TileIndex);

		if ((NextTileName.find("COLLISIONTILES::") != std::string::npos) || (NextTileName.find("ANIMATIONTILES::") != std::string::npos) || (NextTileName.find("RAILTILES::") != std::string::npos))
		{
			if (IsFlip == false)
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
		else
			OnGround = false;
	}
}

void APlayer::MoveRoom()
{
	// Move Room
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FIntPoint CurRoomIndex = GetRoom()->GetGameWorld()->GetCurRoomIndex();

	if (GetActorLocation().X < 0.f)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X - 1, CurRoomIndex.Y });
		AddActorLocation({ WindowSize.X, 0.f });
		MoveValue = FVector2D::ZERO;
		UEngineTimer::GetInst()->TimeStart();
	}
	else if (GetActorLocation().X > WindowSize.X)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X + 1, CurRoomIndex.Y });
		AddActorLocation({ -WindowSize.X, 0.f });
		MoveValue = FVector2D::ZERO;
		UEngineTimer::GetInst()->TimeStart();
	}
	else if (GetActorLocation().Y < 0.f)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X, CurRoomIndex.Y - 1 });
		AddActorLocation({ 0.f, WindowSize.Y });
		MoveValue = FVector2D::ZERO;
		UEngineTimer::GetInst()->TimeStart();
	}
	else if (GetActorLocation().Y > WindowSize.Y)
	{
		GetRoom()->MoveRoom({ CurRoomIndex.X, CurRoomIndex.Y + 1 });
		AddActorLocation({ 0.f, -WindowSize.Y });
		MoveValue = FVector2D::ZERO;
		UEngineTimer::GetInst()->TimeStart();
	}

}

void APlayer::SetCollisionPoint()
{
	if (IsFlip == false)
	{
		PointsY[static_cast<int>(PixelPointY::LeftBottom)] = GetActorTransform().CenterLeftBottom();
		PointsY[static_cast<int>(PixelPointY::Bottom)] = FVector2D(GetActorLocation().X, GetActorLocation().Y + GetActorScale().HalfY());
		PointsY[static_cast<int>(PixelPointY::RightBottom)] = GetActorTransform().CenterRightBottom();

		PointsY[static_cast<int>(PixelPointY::LeftTop)] = GetActorTransform().CenterLeftTop();
		PointsY[static_cast<int>(PixelPointY::Top)] = FVector2D(GetActorLocation().X, GetActorLocation().Y - GetActorScale().HalfY());
		PointsY[static_cast<int>(PixelPointY::RightTop)] = GetActorTransform().CenterRightTop();
	}
	else
	{
		PointsY[static_cast<int>(PixelPointY::LeftBottom)] = GetActorTransform().CenterLeftTop();
		PointsY[static_cast<int>(PixelPointY::Bottom)] = FVector2D(GetActorLocation().X, GetActorLocation().Y - GetActorScale().HalfY());
		PointsY[static_cast<int>(PixelPointY::RightBottom)] = GetActorTransform().CenterRightTop();

		PointsY[static_cast<int>(PixelPointY::LeftTop)] = GetActorTransform().CenterLeftBottom();
		PointsY[static_cast<int>(PixelPointY::Top)] = FVector2D(GetActorLocation().X, GetActorLocation().Y + GetActorScale().HalfY());
		PointsY[static_cast<int>(PixelPointY::RightTop)] = GetActorTransform().CenterRightBottom();
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

}

void APlayer::Reset()
{
	if (GetRoom()->GetGameWorld()->GetCurRoomIndex() != SaveWorldIndex)
		GetRoom()->MoveRoom(SaveWorldIndex);
	SetActorLocation(SaveLocation);
	IsFlip = false;
}

void APlayer::CollisionPlatform()
{

}

void APlayer::CollisionEnermy()
{
}

void APlayer::CollisionSave()
{
}
