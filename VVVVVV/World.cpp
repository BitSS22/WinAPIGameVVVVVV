#include "pch.h"
#include "World.h"
#include "Room.h"

AWorld::AWorld()
{
}

AWorld::~AWorld()
{
}

void AWorld::BeginPlay()
{
	Room = GetWorld()->SpawnActor<ARoom>();
}
