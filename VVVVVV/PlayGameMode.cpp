#include "pch.h"
#include "PlayGameMode.h"
#include "BackGround.h"
#include "GameWorld.h"
#include "Fade.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineSound.h>
#include "Room.h"

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

	EndingSprite = CreateDefaultSubObject<USpriteRenderer>();
	EndingSprite->SetSprite("GameClearTitle", 0);
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	EndingSprite->SetComponentLocation(WindowSize.Half());
	EndingSprite->AddComponentLocation(FVector2D(0.f, -100.f));
	EndingSprite->SetSpriteScale(1.f, 0);
	EndingSprite->SetOrder(ERenderOrder::EndingSprite);
	EndingSprite->SetActive(false);

	Fade = GetWorld()->SpawnActor<AFade>();
}

void APlayGameMode::Tick()
{
	Super::Tick();

	if (GameWorld->GetCurRoomIndex() == EGameConst::ClearRoom && GameClear == false)
	{
		GameClear = true;
		UEngineSound::Play("12 Plenary.mp3");
	}

	if (GameClear == false)
		PlayTime += GET_DELTA;

	if (GameClear == true && Gravitron == false)
	{
		ClearAccTime += GET_DELTA;

		if (ClearAccTime >= 3.f && EndingSprite->IsActive() == false)
			EndingSprite->SetActive(true);

		if (ClearAccTime >= 23.f)
		{
			EndingSprite->SetActive(false);
			Gravitron = true;
			Fade->PlayFadeOut();
		}
	}

	if (Fade->IsFadeOutEnd() == true && Gravitron == true)
		UEngineAPICore::GetCore()->OpenLevel("Title");

	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame) + "DT : " + std::to_string(GET_DELTA));
}

void APlayGameMode::LevelChangeStart()
{
	Fade->PlayFadeIn();
	PlayTime = 0.f;
	ClearAccTime = 0.f;
	GameClear = false;
	Gravitron = false;
}

void APlayGameMode::LevelChangeEnd()
{
}
