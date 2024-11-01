#include "pch.h"
#include "Player.h"
#include "Bullet.h"
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

	SetActorLocation(FVector2D(100.f, 100.f));
	SetActorScale(FVector2D(96.f * 4, 96.f * 4));

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetComponentScale(GetActorScale());
	SpriteRenderer->SetComponentLocation(GetActorLocation());
	SpriteRenderer->SetSprite("player2.png");
	SpriteRenderer->SetOrder(1);

	GetWorld()->SetCameraToMainPawn(false);
	
	SpriteRenderer->CreateAnimation("Teleporter", "player2.png", { 4, 5, 6, 7 }, vector<float>(4, 1.f), true);
	SpriteRenderer->ChangeAnimation("Teleporter", true);
	SpriteRenderer->SetAnimationEvent("Teleporter", 0, bind(&UEngineDebug::OutputString, "x0 y1 \n"));
	SpriteRenderer->SetAnimationEvent("Teleporter", 1, bind(&UEngineDebug::OutputString, "x1 y1 \n"));
	SpriteRenderer->SetAnimationEvent("Teleporter", 2, bind(&UEngineDebug::OutputString, "x2 y1 \n"));
	SpriteRenderer->SetAnimationEvent("Teleporter", 3, bind(&UEngineDebug::OutputString, "x3 y1 \n"));
}

enum class state
{
	up = 1,
	down = -1
};

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

	if (KEY_DOWN('Q'))
		SpriteRenderer->SetOrder(state::up);
	if (KEY_UP('Q'))
		SpriteRenderer->SetOrder(state::down);
	
}