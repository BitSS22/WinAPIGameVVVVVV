#include "pch.h"
#include "PistonEntity.h"
#include "Room.h"
#include "Player.h"

bool APistonEntity::FlipLineCollisionStay = false;
bool APistonEntity::IsCollisionFlipLine = false;

APistonEntity::APistonEntity()
{
}

APistonEntity::~APistonEntity()
{
}

void APistonEntity::BeginPlay()
{
	Super::BeginPlay();

}

void APistonEntity::Tick()
{
	Super::Tick();

	if (GetIsMove() == true && DefualtDir != FVector2D::ZERO)
		AddActorLocation(MoveValue);

	if (DefualtDir != FVector2D::ZERO)
	{
		FTransform Transform = GetActorTransform();
		FVector2D OutDir = AGameWorld::GetRoom()->IsOutScreen(Transform);
		if (OutDir != FVector2D::ZERO)
		{
			FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
			WindowSize += Transform.Scale;
			WindowSize.X *= -OutDir.X;
			WindowSize.Y *= -OutDir.Y;
			AddActorLocation(WindowSize);
		}

		MoveValue = Dir * Speed * GET_DELTA;
		FVector2D NextLocation = GetActorLocation() + MoveValue;
		
		float Diff = (DefualtLocation - NextLocation).Length();

		if (MoveLenght < Diff)
		{
			Dir = -Dir;
			MoveValue += Dir * abs(Diff - MoveLenght) * 2;
		}
	}

	if (IsHide == true)
	{
		AccHideTime += GET_DELTA;

		if (AccHideTime >= HideTime)
			SetActive(false);
	}

	// Debug
	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);

	UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + DefualtDir * MoveLenghtOffset, GetActorScale()), UEngineDebug::EDebugPosType::Rect);
	UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + DefualtDir * MoveLenght, FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
	UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + -DefualtDir * MoveLenght, FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
}

void APistonEntity::SetEntity(const RoomEntityData& _Data)
{
	AEntity::SetEntity(_Data);

	DefualtDir = _Data.DefualtDir;
	Dir = DefualtDir;
	Speed = _Data.Speed;
	MoveLenght = _Data.MoveLenght;
	DefualtLocation = _Data.DefualtLocation;
	SetActorLocation(DefualtLocation);
	MoveLenghtOffset = _Data.MoveLenghtOffset;

	AddActorLocation(Dir * MoveLenghtOffset);
}

RoomEntityData APistonEntity::GetEntityData()
{
	RoomEntityData Data = AEntity::GetEntityData();

	Data.DefualtLocation = DefualtLocation;
	Data.DefualtDir = DefualtDir;
	Data.Speed = Speed;
	Data.MoveLenght = MoveLenght;
	Data.MoveLenghtOffset = MoveLenghtOffset;
	
	return Data;
}

void APistonEntity::Collision(APlayer* _Player)
{
	FTransform PlayerTransform = _Player->GetActorTransform();
	PlayerTransform.Location += _Player->GetMoveValue();
	FTransform Transform = GetActorTransform();
	Transform.Location += GetMoveValue();

	if (FTransform::Collision(ECollisionType::Rect, PlayerTransform, ECollisionType::Rect, Transform) == true)
	{
		switch (GetEntityType())
		{
		case EEntityType::Guy:
			break;
		case EEntityType::Enermy:
			CollisionEnermy(_Player);
			break;
		case EEntityType::Platform:
		case EEntityType::PlatformHide:
			CollisionPlatform(_Player);
			break;
		case EEntityType::FlipLine:
			CollisionFlipLine(_Player);
			FlipLineCollisionStay = true;
			break;
		default:
			MSGASSERT(nullptr, "Not Find Entity Type.");
		}
	}
}

void APistonEntity::CollisionEnermy(APlayer* _Player)
{
	_Player->SetDeath(true);
}

void APistonEntity::CollisionPlatform(APlayer* _Player)
{
	FTransform PlayerTransform = _Player->GetActorTransform();
	FTransform NextPlayerTransform = FTransform(PlayerTransform.Location + _Player->GetMoveValue(), PlayerTransform.Scale);
	FTransform Transform = GetActorTransform();
	FTransform NextTransform = FTransform(Transform.Location + MoveValue, Transform.Scale);

	float Left = NextPlayerTransform.CenterLeft() >= NextTransform.CenterLeft() ? NextPlayerTransform.CenterLeft() : NextTransform.CenterLeft();
	float Right = NextPlayerTransform.CenterRight() <= NextTransform.CenterRight() ? NextPlayerTransform.CenterRight() : NextTransform.CenterRight();
	float Top = NextPlayerTransform.CenterTop() >= NextTransform.CenterTop() ? NextPlayerTransform.CenterTop() : NextTransform.CenterTop();
	float Bottom = NextPlayerTransform.CenterBottom() <= NextTransform.CenterBottom() ? NextPlayerTransform.CenterBottom() : NextTransform.CenterBottom();

	FTransform CollisionRect = {};
	CollisionRect.Scale.Y = Bottom - Top;
	CollisionRect.Scale.X = Right - Left;
	CollisionRect.Location.Y = Top + CollisionRect.Scale.HalfY();
	CollisionRect.Location.X = Left + CollisionRect.Scale.HalfX();

	FVector2D Dir = CollisionRect.Location - NextTransform.Location;
	Dir.X /= NextTransform.Scale.X * 1.5f;
	Dir.Y /= NextTransform.Scale.Y;

	if (Dir.X < Dir.Y && -Dir.X > Dir.Y)
	{
		_Player->SetActorLocation(FVector2D(NextTransform.CenterLeft() - PlayerTransform.Scale.HalfX(), PlayerTransform.Location.Y));
		_Player->SetMoveValue(FVector2D(0.f, _Player->GetMoveValue().Y));

	}
	if (Dir.X > Dir.Y && -Dir.X < Dir.Y)
	{
		_Player->SetActorLocation(FVector2D(NextTransform.CenterRight() + PlayerTransform.Scale.HalfX(), PlayerTransform.Location.Y));
		_Player->SetMoveValue(FVector2D(0.f, _Player->GetMoveValue().Y));
	}

	if (Dir.X < Dir.Y && -Dir.X < Dir.Y)
	{
		_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, NextTransform.CenterBottom() + PlayerTransform.Scale.HalfY()));
		_Player->SetMoveValue(FVector2D(_Player->GetMoveValue().X + MoveValue.X, 0.f));
		_Player->SetGround(true);
		if (GetEntityType() == EEntityType::PlatformHide && _Player->GetFlip() == true && IsHide == false)
			Hide();
	}
	if (Dir.X > Dir.Y && -Dir.X > Dir.Y)
	{
		_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, NextTransform.CenterTop() - PlayerTransform.Scale.HalfY()));
		_Player->SetMoveValue(FVector2D(_Player->GetMoveValue().X + MoveValue.X, 0.f));
		_Player->SetGround(true);
		if (GetEntityType() == EEntityType::PlatformHide && _Player->GetFlip() == false && IsHide == false)
			Hide();
	}
}

void APistonEntity::CollisionFlipLine(APlayer* _Player)
{
	if (IsCollisionFlipLine == true)
		return;

	FVector2D Location = GetActorLocation();
	FVector2D PlayerLocation = _Player->GetActorLocation();
	FVector2D NextPlayerLocation = PlayerLocation + _Player->GetMoveValue();

	string Name = UEngineString::ToUpper("Horizontal");
	if (GetSpriteName().find(Name) != std::string::npos)
	{
		bool PrevLocation = Location.Y - PlayerLocation.Y > 0.f;
		bool NextLocation = Location.Y - NextPlayerLocation.Y > 0.f;

		if (PrevLocation != NextLocation)
		{
			_Player->SetFlip(!_Player->GetFlip());
			IsCollisionFlipLine = true;
			UEngineSound::Play("vanish.wav");
		}
	}
	else
	{
		bool PrevLocation = Location.X - PlayerLocation.X > 0.f;
		bool NextLocation = Location.X - NextPlayerLocation.X > 0.f;

		if (PrevLocation != NextLocation)
		{
			_Player->SetFlip(!_Player->GetFlip());
			IsCollisionFlipLine = true;
			UEngineSound::Play("vanish.wav");
		}
	}

}

void APistonEntity::Hide()
{
	if (IsHide == false)
	{
		ActiveAnimation();
		IsHide = true;
		UEngineSound::Play("vanish.wav");
	}
}

void APistonEntity::AddEntityLocation(const FVector2D& _Location)
{
	SetActorLocation(DefualtLocation += _Location);
	DefualtLocation = GetActorLocation();
	SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
	Dir = DefualtDir;
}

void APistonEntity::AddSpeed(float _Speed)
{
	Speed += _Speed;
	SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
}

void APistonEntity::AddMoveLenght(float _Lenght)
{
	MoveLenght += _Lenght;
	SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
	Dir = DefualtDir;
}

void APistonEntity::AddMoveLenghtOffset(float _Offset)
{
	MoveLenghtOffset += _Offset;
	SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
	Dir = DefualtDir;
}

void APistonEntity::AddDir(const FVector2D& _Dir)
{
	DefualtDir += _Dir;
	if (DefualtDir != FVector2D::ZERO)
		DefualtDir.Nomalize();
	Dir = DefualtDir;
	SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
}

void APistonEntity::SetDir(const FVector2D& _Dir)
{
	DefualtDir = _Dir;
	if (DefualtDir != FVector2D::ZERO)
		DefualtDir.Nomalize();
	Dir = DefualtDir;
	SetActorLocation(DefualtLocation + (DefualtDir * MoveLenghtOffset));
}
