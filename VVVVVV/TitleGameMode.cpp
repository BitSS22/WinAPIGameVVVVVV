#include "pch.h"
#include "TitleGameMode.h"
#include "BackGround.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ABackGround>();
}

void ATitleGameMode::Tick()
{
	Super::Tick();

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}


