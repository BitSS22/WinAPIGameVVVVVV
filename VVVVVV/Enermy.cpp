#include "pch.h"
#include "Enermy.h"

AEnermy::AEnermy()
{
}

AEnermy::~AEnermy()
{
}

void AEnermy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnermy::Tick()
{
	Super::Tick();

	if (Dir != FVector2D::ZERO)
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
	UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + FVector2D::RIGHT * MoveLenghtOffset, GetActorScale()), UEngineDebug::EDebugPosType::Rect);
	UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + Dir * MoveLenght, FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
	UEngineDebug::CoreDebugRender(FTransform(DefualtLocation + -Dir * MoveLenght, FVector2D(5.f, 5.f)), UEngineDebug::EDebugPosType::Circle);
}

void AEnermy::EnermyDefaultSetUp(std::string_view _Name, FVector2D _Location, FVector2D _Dir, float _Speed, float _MoveLength, float _MoveOffset)
{
	AEntity::EntityDefaultSetUp(_Name, _Location);

	Dir = _Dir;
	Speed = _Speed;
	MoveLenght = _MoveLength;
	DefualtLocation = GetActorLocation();
	MoveLenghtOffset = _MoveOffset;
	AddActorLocation(Dir * MoveLenghtOffset);
}
