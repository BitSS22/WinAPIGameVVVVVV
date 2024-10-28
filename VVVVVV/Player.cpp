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

void APlayer::Tick(float _DeltaTime)
{
	if (UEngineInput::GetInst().IsPress('A'))
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	if (UEngineInput::GetInst().IsPress('D'))
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	if (UEngineInput::GetInst().IsPress('W'))
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	if (UEngineInput::GetInst().IsPress('S'))
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
}

