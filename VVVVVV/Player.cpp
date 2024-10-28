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
		AddActorLocation(FVector2D::LEFT * GETDT * Speed);
	if (UEngineInput::GetInst().IsPress('D'))
		AddActorLocation(FVector2D::RIGHT * GETDT * Speed);
	if (UEngineInput::GetInst().IsPress('W'))
		AddActorLocation(FVector2D::UP * GETDT * Speed);
	if (UEngineInput::GetInst().IsPress('S'))
		AddActorLocation(FVector2D::DOWN * GETDT * Speed);
}

