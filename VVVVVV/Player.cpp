#include "pch.h"
#include "Player.h"
#include "Bullet.h"

APlayer::APlayer()
{
	SetActorLocation(FVector2D(100.f, 100.f));
	SetActorScale(FVector2D(50.f, 50.f));

	SetSprite("player.png", 0);
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
	if (false)// KEY_PRESS(VK_LBUTTON))
	{
		POINT CursorPos = {};
		GetCursorPos(&CursorPos);
		ScreenToClient(UEngineAPICore::GetCore()->GetMainWindow().GetWindowHandle(), &CursorPos);
		FVector2D VectorCursor = CursorPos;
		VectorCursor -= GetActorLocation();
		Bullet* NewBullet = GetWorld()->SpawnActor<Bullet>();
		NewBullet->SetActorLocation(GetActorLocation());
		NewBullet->SetDir(VectorCursor.SetNomalize());
	}
	
}