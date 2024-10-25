#include "pch.h"
#include "Level.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	auto iter = AllActors.begin();

	while (iter != AllActors.end())
	{
		delete *iter;
		++iter;
	}

	AllActors.clear();
}

void ULevel::Tick(float _DeltaTime) const
{
	for (const auto& i : AllActors)
		i->Tick(_DeltaTime);
}

void ULevel::Render() const
{
	for (const auto& i : AllActors)
		i->Render();
}

