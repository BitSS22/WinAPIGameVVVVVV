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
	StartPos = GetActorLocation();
	EndPos = GetActorLocation();
}
