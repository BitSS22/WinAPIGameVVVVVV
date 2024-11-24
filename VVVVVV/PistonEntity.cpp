#include "pch.h"
#include "PistonEntity.h"
#include "Room.h"
#include "Player.h"

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

	if (GetIsMove() == true)
		AddActorLocation(MoveValue);

	if (DefualtDir != FVector2D::ZERO)
	{
		MoveValue = Dir * Speed * GET_DELTA;
		FVector2D NextLocation = GetActorLocation() + MoveValue;
		
		float Diff = (DefualtLocation - NextLocation).Length();

		if (MoveLenght < Diff)
		{
			Dir = -Dir;
			MoveValue += Dir * abs(Diff - MoveLenght) * 2;
		}
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

	if (FTransform::Collision(ECollisionType::Rect, PlayerTransform, ECollisionType::Rect, Transform) == false)
		return;

	switch (GetEntityType())
	{
	case EEntityType::Guy:
		return;
	case EEntityType::Enermy:
		CollisionEnermy(_Player);
		return;
	case EEntityType::Platform:
		CollisionPlatform(_Player);
		return;
	case EEntityType::FlipLine:
		CollisionFlipLine(_Player);
		return;
	}

	MSGASSERT(nullptr, "Not Find Entity Type.");
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

	if (Dir.X < Dir.Y && -Dir.X < Dir.Y)
	{
		_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, NextTransform.CenterBottom() + PlayerTransform.Scale.HalfY()));
		_Player->SetMoveValue(FVector2D(_Player->GetMoveValue().X + MoveValue.X, 0.f));
		_Player->SetGround(true);
	}
	if (Dir.X > Dir.Y && -Dir.X > Dir.Y)
	{
		_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, NextTransform.CenterTop() - PlayerTransform.Scale.HalfY()));
		_Player->SetMoveValue(FVector2D(_Player->GetMoveValue().X + MoveValue.X, 0.f));
		_Player->SetGround(true);
	}

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
}

void APistonEntity::CollisionFlipLine(APlayer* _Player)
{








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
