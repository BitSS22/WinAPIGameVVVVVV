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

	if (DefualtDir != FVector2D::ZERO)
	{
		AddActorLocation(Dir * Speed * GET_DELTA);

		float Diff = (DefualtLocation - GetActorLocation()).Length();

		if (MoveLenght < Diff)
		{
			Dir = -Dir;
			AddActorLocation(Dir * abs(Diff - MoveLenght) * 2);
		}
	}

	// Debug
	// 액터 위치
	UEngineDebug::CoreDebugRender(GetActorTransform(), UEngineDebug::EDebugPosType::Rect);

	// 액터 기준 위치
	if (Dir != FVector2D::ZERO)
	{
		UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + DefualtDir * MoveLenghtOffset, GetActorScale()), UEngineDebug::EDebugPosType::Rect);
		UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + DefualtDir * MoveLenght, FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
		UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + -DefualtDir * MoveLenght, FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
	}
}

void APistonEntity::SetEntity(const AGameWorld::RoomData::RoomEntityData& _Data)
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
