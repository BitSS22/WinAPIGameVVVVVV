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

	if (GetRoom()->GetIsEntityMove())
	{
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

void APistonEntity::MoveEntityDefaultSetUp(std::string_view _Name, FVector2D _Location, FVector2D _Dir, float _Speed, float _MoveLength, float _MoveOffset)
{
	AEntity::EntityDefaultSetUp(_Name, _Location);

	DefualtDir = _Dir;
	Dir = DefualtDir;
	Speed = _Speed;
	MoveLenght = _MoveLength;
	DefualtLocation = _Location;
	SetActorLocation(DefualtLocation);
	MoveLenghtOffset = _MoveOffset;
	AddActorLocation(Dir * MoveLenghtOffset);
}
