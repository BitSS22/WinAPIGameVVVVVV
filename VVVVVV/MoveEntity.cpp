#include "pch.h"
#include "MoveEntity.h"

AMoveEntity::AMoveEntity()
{
}

AMoveEntity::~AMoveEntity()
{
}

void AMoveEntity::BeginPlay()
{
	Super::BeginPlay();

}

void AMoveEntity::Tick()
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

void AMoveEntity::MoveEntityDefaultSetUp(std::string_view _Name, FVector2D _Location, FVector2D _Dir, float _Speed, float _MoveLength, float _MoveOffset)
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

	UEngineSprite* Sprite = UImageManager::GetInst().FindSprite(_Name);
	Collider = CreateDefaultSubObject<U2DCollision>();
	Collider->SetComponentScale(Sprite->GetSpriteData(0).Transform.Scale);
	if (_Name.find("PLATFORMS::") != std::string::npos)
		Collider->SetCollisionGroup(ECollisionGroup::Platform);
	else if (_Name.find("SAVE::") != std::string::npos)
		Collider->SetCollisionGroup(ECollisionGroup::Save);
	else
		Collider->SetCollisionGroup(ECollisionGroup::Enermy);
	Collider->SetCollisionType(ECollisionType::Rect);
}
