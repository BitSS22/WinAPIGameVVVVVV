#include "pch.h"
#include "Level.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	AllActors.clear();
}

void ULevel::Tick()
{
	for (const auto& i : AllActors)
		i->Tick();
}

void ULevel::Render()
{
	for (const auto& i : AllActors)
		i->Render();
}

