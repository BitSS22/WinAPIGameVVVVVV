#include "pch.h"
#include "Player.h"
#include "Bullet.h"

APlayer::APlayer()
{
	SetActorLocation(FVector2D(100.f, 100.f));
	SetActorScale(FVector2D(100.f, 100.f));
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APlayer::Tick()
{
	Super::Tick();

	if (UEngineInput::GetInst().IsPress('A'))
		AddActorLocation(FVector2D::LEFT * GET_DELTA * Speed);
	if (UEngineInput::GetInst().IsPress('D'))
		AddActorLocation(FVector2D::RIGHT * GET_DELTA * Speed);
	if (UEngineInput::GetInst().IsPress('W'))
		AddActorLocation(FVector2D::UP * GET_DELTA * Speed);
	if (UEngineInput::GetInst().IsPress('S'))
		AddActorLocation(FVector2D::DOWN * GET_DELTA * Speed);

	if (KEY_DOWN(VK_SPACE))
	{
		Bullet* NewBullet = GetWorld()->SpawnActor<Bullet>();
		NewBullet->SetActorLocation(GetActorLocation());
	}
	UINT frame = UEngineAPICore::GetCore()->GetFrame();
	
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV / FPS : " + std::to_string(frame));
}

