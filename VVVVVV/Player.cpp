#include "pch.h"
#include "Player.h"
#include "Bullet.h"

APlayer::APlayer()
{
	SetActorLocation(FVector2D(100.f, 100.f));
	SetActorScale(FVector2D(96.f, 96.f));

	SetSprite("player2.png", 0);
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
	
	if (KEY_DOWN(VK_LBUTTON))
	{
		AddSpriteIndex(1);
		
		if (GetSpriteIndex() > 15)
			SetSpriteIndex(0);
	}
}