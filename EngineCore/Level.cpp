#include "pch.h"
#include "Level.h"
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>

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
	for (const auto& CurActor : BeginPlayList)
	{
		CurActor->BeginPlay();
		AllActors.push_back(CurActor);
	}

	BeginPlayList.clear();

	AActor::ComponentBeginPlay();

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

	UEngineDebug::PrintEngineDebugText();

	DoubleBuffering();
}

void ULevel::Realease()
{
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

void ULevel::LevelChangeStart()
{
	for (const auto& actor : AllActors)
		actor->LevelChangeStart();
}

void ULevel::LevelChangeEnd()
{
	for (const auto& actor : AllActors)
		actor->LevelChangeEnd();
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

