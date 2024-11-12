#include "pch.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>

APlayer::APlayer()
{
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
	
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Cyan Right", 0);
	SpriteRenderer->SetSpriteScale(1.f, SpriteRenderer->GetCurIndex());
	SpriteRenderer->SetComponentLocation(GetActorScale().Half());
	SpriteRenderer->SetOrder(1);

	SetActorLocation(FVector2D(0.f, 0.f));
	SetActorScale(SpriteRenderer->GetComponentScale());

	GetWorld()->SetCameraToMainPawn(false);
	
	// SpriteRenderer->CreateAnimation("Teleporter", "player2.png", { 4, 5, 6, 7 }, vector<float>(4, 1.f), true);
	// SpriteRenderer->ChangeAnimation("Teleporter", true);
	// SpriteRenderer->SetAnimationEvent("Teleporter", 0, bind(&UEngineDebug::OutputString, "x0 y1 \n"));
	// SpriteRenderer->SetAnimationEvent("Teleporter", 1, bind(&UEngineDebug::OutputString, "x1 y1 \n"));
	// SpriteRenderer->SetAnimationEvent("Teleporter", 2, bind(&UEngineDebug::OutputString, "x2 y1 \n"));
	// SpriteRenderer->SetAnimationEvent("Teleporter", 3, bind(&UEngineDebug::OutputString, "x3 y1 \n"));
}

void APlayer::Tick()
{
	Super::Tick();

	if (UEngineInput::GetInst().IsPress('A'))
	{
		AddActorLocation(FVector2D::LEFT * GET_DELTA * Speed);
	}
	if (UEngineInput::GetInst().IsPress('D'))
	{
		AddActorLocation(FVector2D::RIGHT * GET_DELTA * Speed);
	}
	if (UEngineInput::GetInst().IsPress('W'))
	{
		AddActorLocation(FVector2D::UP * GET_DELTA * Speed);
	}
	if (UEngineInput::GetInst().IsPress('S'))
	{
		AddActorLocation(FVector2D::DOWN * GET_DELTA * Speed);
	}

	SpriteRenderer->SetComponentLocation(GetActorLocation());
}