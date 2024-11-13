#include "pch.h"
#include "PlayGameMode.h"
#include "BackGround.h"
#include "World.h"

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

	World = GetWorld()->SpawnActor<AWorld>();
	World->SetEditMode(false);

	World->LoadFile();
}

void APlayGameMode::Tick()
{
	if (KEY_DOWN('L'))
	{
	}

	Super::Tick();

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}

void APlayGameMode::LevelChangeStart()
{
}


