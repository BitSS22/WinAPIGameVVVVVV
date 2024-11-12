#include "pch.h"
#include "Actor.h"
#include "ActorComponent.h"

list<UActorComponent*> AActor::ComponentBeginList = {};

AActor::AActor()
{
}

AActor::~AActor()
{
	for (const auto& i : Components)
	{
		if (i != nullptr)
			delete i;
	}

	Components.clear();
}

void AActor::Tick()
{
	if (IsDebug() == true)
	{
		FVector2D Pos = GetActorLocation();
		FVector2D CameraPos = GetWorld()->GetCameraPos();

		FTransform Trans = {};
		Trans.Location = Pos - CameraPos;
		Trans.Scale = FVector2D(6.f, 6.f);

		UEngineDebug::CoreDebugRender(Trans, UEngineDebug::EDebugPosType::Circle);
	}

	for (const auto& Component : Components)
		Component->ComponentTick();
}

void AActor::ComponentBeginPlay()
{
	for (const auto& component : ComponentBeginList)
		component->BeginPlay();

	ComponentBeginList.clear();
}

void AActor::ReleaseCheck()
{
	UObject::ReleaseCheck();

	auto iter = Components.begin();
	while (iter != Components.end())
	{
		if ((*iter)->IsDestroy() == false)
		{
			(*iter)->ReleaseCheck();
			++iter;
			continue;
		}

		delete *iter;
		iter = Components.erase(iter);
	}
}

void AActor::ReleaseTimeCheck()
{
	UObject::ReleaseTimeCheck();

	for (auto iter = Components.begin(); iter != Components.end(); ++iter)
	{
		(*iter)->ReleaseTimeCheck();
	}
}
