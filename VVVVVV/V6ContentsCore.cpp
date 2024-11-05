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

	// BackGroud
	UImageManager::GetInst().CreateCutSprite("TitleImage(TempImage).png", "TempTitleImage", FVector2D(0.f, 0.f), FVector2D(640.f, 480.f), FVector2D(0.f, 0.f), 1, 1);

	float X = 704.f;
	float Y = 544.f;

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Cyan", FVector2D(X * 0, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Red", FVector2D(X * 1, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Pink", FVector2D(X * 2, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Blue", FVector2D(X * 3, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Yellow", FVector2D(X * 4, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Green", FVector2D(X * 5, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Horizontal Grey", FVector2D(X * 6, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Cyan", FVector2D(X * 0, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Red", FVector2D(X * 1, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Pink", FVector2D(X * 2, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Blue", FVector2D(X * 3, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Yellow", FVector2D(X * 4, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Green", FVector2D(X * 5, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Vertical Grey", FVector2D(X * 6, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Cyan", FVector2D(640.f * 0, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Red", FVector2D(640.f * 1, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Pink", FVector2D(640.f * 2, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Blue", FVector2D(640.f * 3, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Yellow", FVector2D(640.f * 4, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Green", FVector2D(640.f * 5, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Tower Grey", FVector2D(640.f * 6, Y * 2), FVector2D(640.f, 1920.f), FVector2D(0.f, 0.f), 1, 1);

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Space", FVector2D(4480.f, 1120.f), FVector2D(640.f, 480.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Stars", FVector2D(4480.f, 1088.f), FVector2D(8.f, 8.f), FVector2D(0.f, 0.f), 3, 3);


	// Tile
	X = 192.f;
	Y = 64.f;

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Cyan", FVector2D(X * 0, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Cyan", FVector2D(X * 0, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Cyan", FVector2D(X * 0, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Cyan", FVector2D(X * 0, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Cyan", FVector2D(X * 0, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Cyan", FVector2D(X * 0, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Cyan", FVector2D(X * 0, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Cyan", FVector2D(X * 0, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Cyan", FVector2D(X * 0, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type09 Cyan", FVector2D(X * 0, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type10 Cyan", FVector2D(X * 0, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Pink", FVector2D(X * 1, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Pink", FVector2D(X * 1, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Pink", FVector2D(X * 1, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Pink", FVector2D(X * 1, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Pink", FVector2D(X * 1, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Pink", FVector2D(X * 1, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Pink", FVector2D(X * 1, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Pink", FVector2D(X * 1, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Pink", FVector2D(X * 1, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type09 Pink", FVector2D(X * 1, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type10 Pink", FVector2D(X * 1, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Red", FVector2D(X * 2, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Red", FVector2D(X * 2, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Red", FVector2D(X * 2, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Red", FVector2D(X * 2, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Red", FVector2D(X * 2, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Red", FVector2D(X * 2, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Red", FVector2D(X * 2, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Red", FVector2D(X * 2, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Red", FVector2D(X * 2, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type09 Red", FVector2D(X * 2, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type10 Red", FVector2D(X * 2, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Blue", FVector2D(X * 3, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Blue", FVector2D(X * 3, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Blue", FVector2D(X * 3, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Blue", FVector2D(X * 3, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Blue", FVector2D(X * 3, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Blue", FVector2D(X * 3, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Blue", FVector2D(X * 3, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Blue", FVector2D(X * 3, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Blue", FVector2D(X * 3, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type09 Blue", FVector2D(X * 3, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type10 Blue", FVector2D(X * 3, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Yellow", FVector2D(X * 4, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Yellow", FVector2D(X * 4, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Yellow", FVector2D(X * 4, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Yellow", FVector2D(X * 4, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Yellow", FVector2D(X * 4, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Yellow", FVector2D(X * 4, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Yellow", FVector2D(X * 4, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Yellow", FVector2D(X * 4, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Yellow", FVector2D(X * 4, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type09 Yellow", FVector2D(X * 4, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type10 Yellow", FVector2D(X * 4, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Green", FVector2D(X * 5, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Green", FVector2D(X * 5, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Green", FVector2D(X * 5, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Green", FVector2D(X * 5, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Green", FVector2D(X * 5, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Green", FVector2D(X * 5, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Green", FVector2D(X * 5, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Green", FVector2D(X * 5, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Green", FVector2D(X * 5, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type09 Green", FVector2D(X * 5, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type10 Green", FVector2D(X * 5, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type00 Gray", FVector2D(X * 6, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type01 Gray", FVector2D(X * 6, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type02 Gray", FVector2D(X * 6, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type03 Gray", FVector2D(X * 6, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type04 Gray", FVector2D(X * 6, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type05 Gray", FVector2D(X * 6, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type06 Gray", FVector2D(X * 6, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type07 Gray", FVector2D(X * 6, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Tiles Type08 Gray", FVector2D(X * 6, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Cyan", FVector2D(X * 0, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type01 Cyan", FVector2D(X * 0, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Pink", FVector2D(X * 1, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type01 Pink", FVector2D(X * 1, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Red", FVector2D(X * 2, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type01 Red", FVector2D(X * 2, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Blue", FVector2D(X * 3, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type01 Blue", FVector2D(X * 3, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Yellow", FVector2D(X * 4, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type01 Yellow", FVector2D(X * 4, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Green", FVector2D(X * 5, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type01 Green", FVector2D(X * 5, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGround Tiles Type00 Gray", FVector2D(X * 6, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Cyan", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Pink", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Red", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Blue", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Yellow", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Green", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Grey", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Spike Defualt", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);


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


	// TODO. Create Animation



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
	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void V6ContentsCore::Tick()
{
	// UNUSED 현재 사용 하지 않는 함수
}
