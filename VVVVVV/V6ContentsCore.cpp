#include "pch.h"
#include "V6ContentsCore.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "PlayGameMode.h"
#include "Player.h"

V6ContentsCore::V6ContentsCore()
{
}

V6ContentsCore::~V6ContentsCore()
{
}

void V6ContentsCore::BeginPlay()
{
	UEngineDirectory Dir = {};
	if (Dir.MoveParentToDirectory("Resources") == false)
		MSGASSERT(nullptr, "Resources 폴더가 없습니다.");

	vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); ++i)
	{
		string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	UImageManager::GetInst().CutSprite("player.png", FVector2D(12, 24));


	///////////////////////////////////////////////////////////////////////


	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV");

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosScale(FVector2D(0.f, 0.f), FVector2D(1280.f, 720.f));

	// UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	// UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Play");
}

void V6ContentsCore::Tick()
{
	// UNUSED 현재 사용 하지 않는 함수
}
