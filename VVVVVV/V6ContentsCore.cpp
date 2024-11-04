#include "pch.h"
#include "V6ContentsCore.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "EndingGameMode.h"
#include "TileMapEditorMode.h"

#include "Player.h"

V6ContentsCore::V6ContentsCore()
{
}

V6ContentsCore::~V6ContentsCore()
{
}

void V6ContentsCore::BeginPlay()
{
	// Image Load
	UEngineDirectory Dir = {};
	Dir.MoveParentToDirectory("Resources");
	vector<UEngineFile> ImageFiles = Dir.GetAllFile();
	
	for (const auto& image : ImageFiles)
		UImageManager::GetInst().Load(image.GetPathToString());
	

	// Create Sprite TODO.
	
	// Title Level
	// Logo
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "Logo", FVector2D(318.f, 26.f), FVector2D(64.f, 64.f), FVector2D(0.f, 0.f), 1, 1);
	// Backgroud Pattern 
	UImageManager::GetInst().CreateCutSprite("Main BackGround.png", "TitleBackGround", FVector2D(8.f, 130.f), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);

	// Play Level
	// Tile
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles", FVector2D(0.f, 0.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "NoneTile", FVector2D(640.f, 480.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	
	// Background Object
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "SadElephant", FVector2D(8.f, 182.f), FVector2D(928.f, 640.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "PlayTimeIcon", FVector2D(318.f, 126.f), FVector2D(34.f, 34.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "CommsRelayRadar", FVector2D(834.f, 26.f), FVector2D(128.f, 128.f), FVector2D(6.f, 0.f), 4, 4);

	// Event Object
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "Terminal", FVector2D(8.f, 26.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "WarpToken", FVector2D(8.f, 78.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "CheckPoint", FVector2D(8.f, 130.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "Trinket", FVector2D(162.f, 26.f), FVector2D(32.f, 32.f), FVector2D(0.f, 0.f), 1, 1);

	// Player
	// HappyPlayer
	UImageManager::GetInst().CreateCutSprite("Player.png", "RightPlayer", FVector2D(8.f, 26.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "LeftPlayer", FVector2D(66.f, 26.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "ReverseRightPlayer", FVector2D(126.f, 26.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "ReverseLeftPlayer", FVector2D(184.f, 26.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	// SadPlayer
	UImageManager::GetInst().CreateCutSprite("Player.png", "SadRightPlayer", FVector2D(8.f, 88.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "SadLeftPlayer", FVector2D(66.f, 88.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "SadReverseRightPlayer", FVector2D(126.f, 88.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "SadReverseLeftPlayer", FVector2D(184.f, 88.f), FVector2D(24.f, 42.f), FVector2D(6.f, 0.f), 2, 2);
	
	// Ending Level
	// Ending Image
	UImageManager::GetInst().CreateCutSprite("EndingScreen.png", "EndingImage", FVector2D(8.f, 26.f), FVector2D(640.f, 480.f), FVector2D(0.f, 0.f), 1, 1);


	// Create Animation TODO.

	

	// Init Window Pos & Scale
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VVVVVV");
	FVector2D WindowResolution = FVector2D(width, height);
	FVector2D InitWindowScale = FVector2D(640, 480);
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosScale(WindowResolution.Half() - InitWindowScale.Half(), InitWindowScale);


	// Create Level
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Play");
	UEngineAPICore::GetCore()->CreateLevel<AEndingGameMode, AActor>("End");
	UEngineAPICore::GetCore()->CreateLevel<ATileMapEditorMode, AActor>("TileMapEditor");


	// Open Level
	UEngineAPICore::GetCore()->OpenLevel("TileMapEditor");
}

void V6ContentsCore::Tick()
{
	// UNUSED 현재 사용 하지 않는 함수
}
