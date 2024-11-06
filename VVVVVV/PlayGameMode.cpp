#include "pch.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	USpriteRenderer* map = GetWorld()->SpawnActor<USpriteRenderer>();
	map->SetSprite("TempTitleImage", 0);
	map->SetComponentLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
}

void APlayGameMode::Tick()
{
	Super::Tick();

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}


