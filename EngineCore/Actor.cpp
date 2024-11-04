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
