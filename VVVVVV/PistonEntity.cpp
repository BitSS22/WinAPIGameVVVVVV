#include "pch.h"
#include "PistonEntity.h"
#include "Room.h"

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

	if ((GetActorLocation() - DefualtLocation).Length() > MoveLenght)
		int a = 0;


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
