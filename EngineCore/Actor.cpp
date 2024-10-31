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

void AActor::ComponentBeginPlay()
{
	for (const auto& component : ComponentBeginList)
		component->BeginPlay();

	ComponentBeginList.clear();
}
