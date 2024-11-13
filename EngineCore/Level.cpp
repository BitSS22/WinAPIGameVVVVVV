#include "pch.h"
#include "Level.h"
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>
#include "2DCollision.h"

std::vector<CollisionLinkData> ULevel::CollisionLink = {};

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	for (const auto& actor : BeginPlayList)
		delete actor;

	for (const auto& actor : AllActors)
		delete actor;
	
	AllActors.clear();
}

void ULevel::Tick()
{
	BeginPlayCheck();

	for (const auto& CurActor : AllActors)
	{
		if (CurActor->IsActive() == false)
			continue;
		CurActor->Tick();
	}
}

void ULevel::Render()
{
	ScreenClear();

	if (IsCameraToMainPawn == true)
		CameraPos = MainPawn->GetActorLocation() + CameraPivot;

	for (const auto& FirstActor : Renderers)
	{
		for (const auto& SecondActor : FirstActor.second)
		{
			if (SecondActor->IsActive() == false)
				continue;
			SecondActor->Render();
		}
	}

	UEngineDebug::PrintEngineDebugRender();

	DoubleBuffering();
}

void ULevel::Realease()
{
	for (auto iter = AllActors.begin(); iter != AllActors.end(); ++iter)
	{
		(*iter)->ReleaseTimeCheck();
	}

	for (auto iter = Collisions.begin(); iter != Collisions.end(); ++iter)
	{
		for (auto Seconditer = iter->second.begin(); Seconditer != iter->second.end();)
		{
			if ((*Seconditer)->IsDestroy() == false)
				++Seconditer;
			else
				Seconditer = iter->second.erase(Seconditer);
		}
	}

	for (auto iter = CheckCollisions.begin(); iter != CheckCollisions.end(); ++iter)
	{
		for (auto Seconditer = iter->second.begin(); Seconditer != iter->second.end();)
		{
			if ((*Seconditer)->IsDestroy() == false)
				++Seconditer;
			else
				Seconditer = iter->second.erase(Seconditer);
		}
	}

	for (auto iter = Renderers.begin(); iter != Renderers.end(); ++iter)
	{
		for (auto Seconditer = iter->second.begin(); Seconditer != iter->second.end();)
		{
			if ((*Seconditer)->IsDestroy() == false)
				++Seconditer;
			else
				Seconditer = iter->second.erase(Seconditer);
		}
	}

	for (auto iter = AllActors.begin(); iter != AllActors.end();)
	{
		if ((*iter)->IsDestroy() == false)
		{
			(*iter)->ReleaseCheck();
			++iter;
		}
		else
		{
			delete *iter;
			iter = AllActors.erase(iter);
		}
	}
}

void ULevel::Collision()
{
	for (size_t i = 0; i < CollisionLink.size(); ++i)
	{
		int Left = CollisionLink[i].Left;
		int Right = CollisionLink[i].Right;

		const auto& LeftList = CheckCollisions[Left];
		const auto& RightList = Collisions[Right];

		for (const auto& LeftCollision : LeftList)
		{
			if (LeftCollision->IsActive() == false)
				continue;

			for (const auto& RightCollision : RightList)
			{
				if (RightCollision->IsActive() == false)
					continue;

				LeftCollision->CollisionEventCheck(RightCollision);
			}
		}
	}
}

void ULevel::LevelChangeStart()
{
	BeginPlayCheck();

	for (const auto& CurActor : BeginPlayList)
		CurActor->LevelChangeStart();
	for (const auto& CurActor : AllActors)
		CurActor->LevelChangeStart();
}

void ULevel::LevelChangeEnd()
{
	for (const auto& CurActor : BeginPlayList)
		CurActor->LevelChangeEnd();
	for (const auto& CurActor : AllActors)
		CurActor->LevelChangeEnd();
}

void ULevel::CollisionEventCheck(U2DCollision* _Left, U2DCollision* _Right)
{
}

void ULevel::DoubleBuffering()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWindowImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWindowImage* BackBufferImage = MainWindow.GetBackBufferImage();

	FTransform size = {};
	size.Location = MainWindow.GetWindowSize().Half();
	size.Scale = MainWindow.GetWindowSize();

	WindowImage->CopyBit(BackBufferImage, size);
}

void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWindowImage* BackBufferImage = MainWindow.GetBackBufferImage();
	FVector2D size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -1, -1, size.iX() + 1, size.iY() + 1);
}

void ULevel::BeginPlayCheck()
{
	for (const auto& CurActor : BeginPlayList)
	{
		CurActor->BeginPlay();
		AllActors.push_back(CurActor);
	}

	BeginPlayList.clear();

	AActor::ComponentBeginPlay();
}

