#include "pch.h"
#include "Level.h"
#include <EngineBase/EngineMath.h>
#include <EngineCore/SpriteRenderer.h>

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	auto iter = AllActors.begin();

	while (iter != AllActors.end())
	{
		delete *iter;
		++iter;
	}

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
		CurActor->Tick();
}

void ULevel::Render()
{
	ScreenClear();

	for (const auto& FirstActor : Renderers)
	{
		for (const auto& SecondActor : FirstActor.second)
		{
			SecondActor->Render();
		}
	}

	DoubleBuffering();
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

