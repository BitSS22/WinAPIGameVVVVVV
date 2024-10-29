#include "pch.h"
#include "Player.h"

APlayer::APlayer()
{
	SetActorLocation({ 100, 100 });
	SetActorScale({ 100, 100 });
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
}

void APlayer::Tick()
{
	if (UEngineInput::GetInst().IsPress('A'))
		AddActorLocation(FVector2D::LEFT * GET_DELTA * Speed);
	if (UEngineInput::GetInst().IsPress('D'))
		AddActorLocation(FVector2D::RIGHT * GET_DELTA * Speed);
	if (UEngineInput::GetInst().IsPress('W'))
		AddActorLocation(FVector2D::UP * GET_DELTA * Speed);
	if (UEngineInput::GetInst().IsPress('S'))
		AddActorLocation(FVector2D::DOWN * GET_DELTA * Speed);
}

