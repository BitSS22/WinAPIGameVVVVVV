#include "pch.h"
#include "PlayGameMode.h"
#include "BackGround.h"
#include "GameWorld.h"

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

	GameWorld = GetWorld()->SpawnActor<AGameWorld>();
	GameWorld->SetEditMode(false);

	GameWorld->LoadFile();
}

void APlayGameMode::Tick()
{
	Super::Tick();

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}

void APlayGameMode::LevelChangeStart()
{
}


