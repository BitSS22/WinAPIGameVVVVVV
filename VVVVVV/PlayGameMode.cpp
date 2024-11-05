#include "pch.h"
#include "PlayGameMode.h"

#include <EngineCore/Level.h>
#include "BackGround.h"

APlayGameMode::APlayGameMode()
{
}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	ABackGround* map = GetWorld()->SpawnActor<ABackGround>();
}

void APlayGameMode::Tick()
{
	Super::Tick();

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}


