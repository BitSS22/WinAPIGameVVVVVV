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

	// FVector2D PlayerPoint = NextPlayerTransform.Location;

	/*if (PlayerPoint.X > Transform.Location.X)
		PlayerPoint.X = NextPlayerTransform.CenterRight();
	else
		PlayerPoint.X = NextPlayerTransform.CenterLeft();

	if (_Player->GetFlip() == false)
		PlayerPoint.Y = NextPlayerTransform.CenterBottom();
	else
		PlayerPoint.Y = NextPlayerTransform.CenterTop();*/



	/*if (_Player->GetFlip() == false)
	{
		if (NextPlayerTransform.CenterBottom() >= NextTransform.CenterTop())
		{
			_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X + MoveValue.X, NextTransform.CenterTop() - PlayerTransform.Scale.HalfY()));
			_Player->SetGround(true);
		}
	}
	else
	{
		if (NextPlayerTransform.CenterTop() <= NextTransform.CenterBottom())
		{
			_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X + MoveValue.X, NextTransform.CenterBottom() + PlayerTransform.Scale.HalfY()));
			_Player->SetGround(true);
		}
	}*/

	if (NextPlayerTransform.CenterLeft() <= NextTransform.CenterRight())
	{
		_Player->SetActorLocation(FVector2D(NextTransform.CenterRight() + PlayerTransform.Scale.HalfX(), PlayerTransform.Location.Y));
		_Player->SetMoveValue(FVector2D(0.f, _Player->GetMoveValue().Y));
	}

	if (NextPlayerTransform.CenterRight() >= NextTransform.CenterLeft())
	{
		_Player->SetActorLocation(FVector2D(NextTransform.CenterLeft() - PlayerTransform.Scale.HalfX(), PlayerTransform.Location.Y));
		_Player->SetMoveValue(FVector2D(0.f, _Player->GetMoveValue().Y));
	}

	/*if (PlayerPoint.X >= NextTransform.CenterLeft() && PlayerPoint.Y >= NextTransform.CenterTop() && PlayerPoint.Y <= NextTransform.CenterBottom())
	{
		_Player->SetActorLocation(FVector2D(NextTransform.CenterLeft() - PlayerTransform.Scale.HalfX(), PlayerTransform.Location.Y));
	}

	if (PlayerPoint.X <= NextTransform.CenterRight() && PlayerPoint.Y >= NextTransform.CenterTop() && PlayerPoint.Y <= NextTransform.CenterBottom())
	{
		_Player->SetActorLocation(FVector2D(NextTransform.CenterRight() + PlayerTransform.Scale.HalfX(), PlayerTransform.Location.Y));
	}*/













	/*FTransform Transform = GetActorTransform();
	FTransform NextTransform = FTransform(Transform.Location + MoveValue, Transform.Scale);
	FTransform PlayerTransform = _Player->GetActorTransform();
	FVector2D PlayerMoveValue = _Player->GetMoveValue();
	FTransform NextPlayerTransform = FTransform(PlayerTransform.Location + _Player->GetMoveValue(), PlayerTransform.Scale);

	static float PlayerTop = PlayerTransform.CenterTop();
	static float PlayerBottom = PlayerTransform.CenterBottom();
	static float PlayerLeft = PlayerTransform.CenterLeft();
	static float PlayerRight = PlayerTransform.CenterRight();

	if (PlayerTransform.CenterBottom() <= Transform.CenterTop() && NextPlayerTransform.CenterBottom() >= NextTransform.CenterTop())
	{
		if (PlayerBottom >= NextTransform.CenterTop() - PlayerTransform.Scale.HalfY())
		{
			PlayerBottom = NextTransform.CenterTop() - PlayerTransform.Scale.HalfY();
			_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, PlayerBottom));
			_Player->SetMoveValue(PlayerMoveValue + MoveValue);
			_Player->SetGround(true);
		}
	}

	if (PlayerTransform.CenterTop() >= Transform.CenterBottom() && NextPlayerTransform.CenterTop() <= NextTransform.CenterBottom())
	{
		if (PlayerTop >= NextTransform.CenterBottom() + PlayerTransform.Scale.HalfY())
		{
			PlayerTop = NextTransform.CenterBottom() + PlayerTransform.Scale.HalfY();
			_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, PlayerBottom));
			_Player->SetMoveValue(PlayerMoveValue + MoveValue);
			_Player->SetGround(true);
		}
	}*/

	/*if (PlayerTransform.CenterBottom() <= Transform.CenterTop() && NextPlayerTransform.CenterBottom() >= NextTransform.CenterTop())
	{
		_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, NextTransform.CenterTop() - PlayerTransform.Scale.HalfY()));
		_Player->SetMoveValue(FVector2D(PlayerMoveValue.X + MoveValue.X, PlayerMoveValue.Y));
		_Player->SetGround(true);
	}

	if (PlayerTransform.CenterTop() >= Transform.CenterBottom() && NextPlayerTransform.CenterTop() <= NextTransform.CenterBottom())
	{
		_Player->SetActorLocation(FVector2D(PlayerTransform.Location.X, NextTransform.CenterBottom() + PlayerTransform.Scale.HalfY()));
		_Player->SetMoveValue(FVector2D(PlayerMoveValue.X + MoveValue.X, PlayerMoveValue.Y));
		_Player->SetGround(true);
	}*/

	//if (PlayerTransform.CenterRight() - 0.001f <= Transform.CenterLeft() && NextPlayerTransform.CenterRight() >= NextTransform.CenterLeft())
	//{
	//	_Player->SetActorLocation(FVector2D(NextTransform.CenterLeft() - PlayerTransform.Scale.HalfX() - 0.001f, PlayerTransform.Location.Y));
	//	_Player->SetMoveValue(FVector2D(0.f, PlayerMoveValue.Y));
	//}
	//if (PlayerTransform.CenterLeft() + 0.001f >= Transform.CenterRight() && NextPlayerTransform.CenterLeft() <= NextTransform.CenterRight())
	//{
	//	_Player->SetActorLocation(FVector2D(NextTransform.CenterRight() + PlayerTransform.Scale.HalfX() + 0.001f, PlayerTransform.Location.Y));
	//	_Player->SetMoveValue(FVector2D(0.f, PlayerMoveValue.Y));
	//}
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
