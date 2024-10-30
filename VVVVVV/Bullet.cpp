#include "pch.h"
#include "Bullet.h"

Bullet::Bullet()
{
	SetActorScale(FVector2D(10.f, 10.f));
}

Bullet::~Bullet()
{
}

void Bullet::BeginPlay()
{
	Super::BeginPlay();
}

void Bullet::Tick()
{
	Super::Tick();

	AddActorLocation(Dir * GET_DELTA * 500.f);

	FVector2D ActorLocation = GetActorLocation();
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	
	if (ActorLocation.X <= 0)
	{
		SetActorLocation(FVector2D(abs(ActorLocation.X), ActorLocation.Y));
		Dir.X *= -1;
	}
	else if (ActorLocation.X >= WindowSize.X)
	{
		float Dist = WindowSize.X - ActorLocation.X;
		SetActorLocation(FVector2D(WindowSize.X - abs(Dist), ActorLocation.Y));
		
		Dir.X *= -1;
	}

	if (ActorLocation.Y <= 0)
	{
		SetActorLocation(FVector2D(ActorLocation.X, abs(ActorLocation.Y)));
		Dir.Y *= -1;
	}
	else if (ActorLocation.Y >= WindowSize.Y)
	{
		float Dist = WindowSize.Y - ActorLocation.Y;
		SetActorLocation(FVector2D(ActorLocation.X, WindowSize.Y - abs(Dist)));

		Dir.Y *= -1;
	}
}
