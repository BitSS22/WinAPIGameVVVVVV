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

	GetWorld()->CollisionGroupLink(ECollisionGroup::Player, ECollisionGroup::Entity);
}

void APlayGameMode::Tick()
{
	Super::Tick();

	if (KEY_PRESS(VK_CONTROL) && KEY_PRESS(VK_SHIFT) && KEY_PRESS(VK_MENU) && KEY_DOWN(VK_SPACE))
		UEngineAPICore::GetCore()->OpenLevel("TileMapEditor");

	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}

void APlayGameMode::LevelChangeStart()
{
}


