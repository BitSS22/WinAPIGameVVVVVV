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
	SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("BackGrounds::15 Tower Cyan", 0);
	Sprite->SetSpriteScale(1.f, 0);
	Sprite->SetOrder(ERenderOrder::BACKGROUND);
}

void ATitleGameMode::Tick()
{
	Super::Tick();

	Sprite->AddComponentLocation(FVector2D::UP * 64.f * GET_DELTA);
	if (Sprite->GetComponentLocation().Y < UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half().Y - 960.f)
		Sprite->AddComponentLocation(FVector2D(0.f, 1920.f));



	if (KEY_DOWN(VK_RETURN))
		UEngineAPICore::GetCore()->OpenLevel("Play");

	UINT frame = UEngineAPICore::GetCore()->GetFrame();

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}


