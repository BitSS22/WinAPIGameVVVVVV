#include "pch.h"
#include "2DCollision.h"

U2DCollision::U2DCollision()
{
}

U2DCollision::~U2DCollision()
{
}

void U2DCollision::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionGroup < 0)
		MSGASSERT(nullptr, "Collision Group은 양수로 지정해 주세요.");

	GetActor()->GetWorld()->PushCollision(this);
}

void U2DCollision::ComponentTick()
{
	Super::ComponentTick();

	if (IsDebug() == true || GetActor()->IsDebug() == true)
	{
		FTransform ActorTransform = GetComponentTransform();
		FVector2D CameraPos = GetActor()->GetWorld()->GetCameraPos();

		ActorTransform.Location -= CameraPos;

		UEngineDebug::CoreDebugRender(ActorTransform, UEngineDebug::EDebugPosType::Circle);
	}
}

