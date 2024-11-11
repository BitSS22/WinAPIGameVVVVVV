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

	ResourceLoad();

	// Open Level
	UEngineAPICore::GetCore()->OpenLevel("TileMapEditor");
}

void V6ContentsCore::Tick()
{
	// UNUSED 현재 사용 하지 않는 함수
}

void V6ContentsCore::ResourceLoad()
{
	UEngineDirectory Dir = {};
	Dir.MoveParentToDirectory("Resources");
	vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (const auto& image : ImageFiles)
		UImageManager::GetInst().Load(image.GetPathToString());

	ResourceSpriteLoad();

}

void V6ContentsCore::ResourceSpriteLoad()
{
	TileImageLoad();
	BackGroundImageLoad();
	PlayerImageLoad();
	FontImageLoad();
	BackGroundObjectImageLoad();
	InterObjectImageLoad();
}

void V6ContentsCore::TileImageLoad()
{
	float X = 192.f;
	float Y = 64.f;
	 
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "None Tile", FVector2D(80.f, 832.f + 16.f * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::01 Type00 Cyan", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::02 Type01 Cyan", FVector2D(X * 0, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::03 Type00 Pink", FVector2D(X * 1, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::04 Type01 Pink", FVector2D(X * 1, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::05 Type00 Red", FVector2D(X * 2, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::06 Type01 Red", FVector2D(X * 2, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::07 Type00 Blue", FVector2D(X * 3, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::08 Type01 Blue", FVector2D(X * 3, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::09 Type00 Yellow", FVector2D(X * 4, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::10 Type01 Yellow", FVector2D(X * 4, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::11 Type00 Green", FVector2D(X * 5, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::12 Type01 Green", FVector2D(X * 5, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::13 Type00 Gray", FVector2D(X * 6, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::14 Bridge Cyan", FVector2D(128.f, 832.f + 16.f * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::15 Bridge Pink", FVector2D(128.f, 832.f + 16.f * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::16 Bridge Red", FVector2D(128.f, 832.f + 16.f * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::17 Bridge Blue", FVector2D(128.f, 832.f + 16.f * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::18 Bridge Yellow", FVector2D(128.f, 832.f + 16.f * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::19 Bridge Green", FVector2D(128.f, 832.f + 16.f * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::20 Bridge Grey", FVector2D(128.f, 832.f + 16.f * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 3);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::21 Tower Cyan", FVector2D(384.f + 16.f * 0, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::22 Tower Pink", FVector2D(384.f + 16.f * 1, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::23 Tower Red", FVector2D(384.f + 16.f * 2, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::24 Tower Blue", FVector2D(384.f + 16.f * 3, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::25 Tower Yellow", FVector2D(384.f + 16.f * 4, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::26 Tower Green", FVector2D(384.f + 16.f * 5, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::27 Tower Grey", FVector2D(384.f + 16.f * 6, 832.f), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
	

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::01 Type00 Cyan", FVector2D(X * 0, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::02 Type01 Cyan", FVector2D(X * 0, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::03 Type02 Cyan", FVector2D(X * 0, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::04 Type03 Cyan", FVector2D(X * 0, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::05 Type04 Cyan", FVector2D(X * 0, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::06 Type05 Cyan", FVector2D(X * 0, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::07 Type06 Cyan", FVector2D(X * 0, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::08 Type07 Cyan", FVector2D(X * 0, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::09 Type08 Cyan", FVector2D(X * 0, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::10 Type09 Cyan", FVector2D(X * 0, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::11 Type10 Cyan", FVector2D(X * 0, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::12 Type00 Pink", FVector2D(X * 1, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::13 Type01 Pink", FVector2D(X * 1, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::14 Type02 Pink", FVector2D(X * 1, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::15 Type03 Pink", FVector2D(X * 1, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::16 Type04 Pink", FVector2D(X * 1, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::17 Type05 Pink", FVector2D(X * 1, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::18 Type06 Pink", FVector2D(X * 1, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::19 Type07 Pink", FVector2D(X * 1, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::20 Type08 Pink", FVector2D(X * 1, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::21 Type09 Pink", FVector2D(X * 1, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::22 Type10 Pink", FVector2D(X * 1, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::23 Type00 Red", FVector2D(X * 2, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::24 Type01 Red", FVector2D(X * 2, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::25 Type02 Red", FVector2D(X * 2, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::26 Type03 Red", FVector2D(X * 2, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::27 Type04 Red", FVector2D(X * 2, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::28 Type05 Red", FVector2D(X * 2, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::29 Type06 Red", FVector2D(X * 2, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::30 Type07 Red", FVector2D(X * 2, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::31 Type08 Red", FVector2D(X * 2, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::32 Type09 Red", FVector2D(X * 2, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::33 Type10 Red", FVector2D(X * 2, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::34 Type00 Blue", FVector2D(X * 3, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::35 Type01 Blue", FVector2D(X * 3, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::36 Type02 Blue", FVector2D(X * 3, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::37 Type03 Blue", FVector2D(X * 3, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::38 Type04 Blue", FVector2D(X * 3, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::39 Type05 Blue", FVector2D(X * 3, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::40 Type06 Blue", FVector2D(X * 3, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::41 Type07 Blue", FVector2D(X * 3, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::42 Type08 Blue", FVector2D(X * 3, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::43 Type09 Blue", FVector2D(X * 3, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::44 Type10 Blue", FVector2D(X * 3, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::45 Type00 Yellow", FVector2D(X * 4, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::46 Type01 Yellow", FVector2D(X * 4, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::47 Type02 Yellow", FVector2D(X * 4, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::48 Type03 Yellow", FVector2D(X * 4, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::49 Type04 Yellow", FVector2D(X * 4, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::50 Type05 Yellow", FVector2D(X * 4, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::51 Type06 Yellow", FVector2D(X * 4, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::52 Type07 Yellow", FVector2D(X * 4, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::53 Type08 Yellow", FVector2D(X * 4, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::54 Type09 Yellow", FVector2D(X * 4, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::55 Type10 Yellow", FVector2D(X * 4, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::56 Type00 Green", FVector2D(X * 5, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::57 Type01 Green", FVector2D(X * 5, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::58 Type02 Green", FVector2D(X * 5, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::59 Type03 Green", FVector2D(X * 5, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::60 Type04 Green", FVector2D(X * 5, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::61 Type05 Green", FVector2D(X * 5, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::62 Type06 Green", FVector2D(X * 5, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::63 Type07 Green", FVector2D(X * 5, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::64 Type08 Green", FVector2D(X * 5, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::65 Type09 Green", FVector2D(X * 5, Y * 9), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::66 Type10 Green", FVector2D(X * 5, Y * 10), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::67 Type00 Gray", FVector2D(X * 6, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::68 Type01 Gray", FVector2D(X * 6, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::69 Type02 Gray", FVector2D(X * 6, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::70 Type03 Gray", FVector2D(X * 6, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::71 Type04 Gray", FVector2D(X * 6, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::72 Type05 Gray", FVector2D(X * 6, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::73 Type06 Gray", FVector2D(X * 6, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::74 Type07 Gray", FVector2D(X * 6, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "CollisionTiles::75 Type08 Gray", FVector2D(X * 6, Y * 8), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "AnimationTiles::01 Animation Cyan", FVector2D(192.f, 832.f + 16.f * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "AnimationTiles::02 Animation Pink", FVector2D(192.f, 832.f + 16.f * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "AnimationTiles::03 Animation Red", FVector2D(192.f, 832.f + 16.f * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "AnimationTiles::04 Animation Blue", FVector2D(192.f, 832.f + 16.f * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "AnimationTiles::05 Animation Yellow", FVector2D(192.f, 832.f + 16.f * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "AnimationTiles::06 Animation Green", FVector2D(192.f, 832.f + 16.f * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 12);


	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::01 Rail Left Cyan", FVector2D(256.f, 16.f * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::02 Rail Left Pink", FVector2D(256.f, 16.f * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::03 Rail Left Red", FVector2D(256.f, 16.f * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::04 Rail Left Blue", FVector2D(256.f, 16.f * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::05 Rail Left Yellow", FVector2D(256.f, 16.f * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::06 Rail Left Green", FVector2D(256.f, 16.f * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::07 Rail Left Grey", FVector2D(256.f, 16.f * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);

	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::08 Rail Right Cyan", FVector2D(320.f, 16.f * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::09 Rail Right Pink", FVector2D(320.f, 16.f * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::10 Rail Right Red", FVector2D(320.f, 16.f * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::11 Rail Right Blue", FVector2D(320.f, 16.f * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::12 Rail Right Yellow", FVector2D(320.f, 16.f * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::13 Rail Right Green", FVector2D(320.f, 16.f * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "RailTiles::14 Rail Right Grey", FVector2D(320.f, 16.f * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::01 Cyan", FVector2D(0.f, 832.f + 16.f * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::02 Pink", FVector2D(0.f, 832.f + 16.f * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::03 Red", FVector2D(0.f, 832.f + 16.f * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::04 Blue", FVector2D(0.f, 832.f + 16.f * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::05 Yellow", FVector2D(0.f, 832.f + 16.f * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::06 Green", FVector2D(0.f, 832.f + 16.f * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::07 Grey", FVector2D(0.f, 832.f + 16.f * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 8, 8);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "SpikeTiles::08 Defualt", FVector2D(0.f, 832.f + 16.f * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 4, 4);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "Debug Tile", FVector2D(64.f, 832.f + 16.f * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);
}

void V6ContentsCore::BackGroundImageLoad()
{
	float X = 672.f;
	float Y = 480.f;

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::00 Space", FVector2D(0.f, 3392.f), FVector2D(640.f, 480.f), FVector2D(0.f, 0.f), 1, 1);

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::01 Horizontal Cyan", FVector2D(X * 0, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::02 Horizontal Red", FVector2D(X * 1, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::03 Horizontal Pink", FVector2D(X * 2, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::04 Horizontal Blue", FVector2D(X * 3, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::05 Horizontal Yellow", FVector2D(X * 4, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::06 Horizontal Green", FVector2D(X * 5, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::07 Horizontal Grey", FVector2D(X * 6, 0.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);

	X = 640.f;
	Y = 512.f;

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::08 Vertical Cyan", FVector2D(X * 0, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::09 Vertical Red", FVector2D(X * 1, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::10 Vertical Pink", FVector2D(X * 2, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::11 Vertical Blue", FVector2D(X * 3, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::12 Vertical Yellow", FVector2D(X * 4, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::13 Vertical Green", FVector2D(X * 5, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::14 Vertical Grey", FVector2D(X * 6, 480.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);

	X = 640.f;
	Y = 2400.f;

	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::15 Tower Cyan", FVector2D(X * 0, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::16 Tower Red", FVector2D(X * 1, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::17 Tower Pink", FVector2D(X * 2, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::18 Tower Blue", FVector2D(X * 3, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::19 Tower Yellow", FVector2D(X * 4, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::20 Tower Green", FVector2D(X * 5, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "BackGrounds::21 Tower Grey", FVector2D(X * 6, 992.f), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);

	// Ending Image
	UImageManager::GetInst().CreateCutSprite("EndingScreen.png", "BackGrounds::22 Ending", FVector2D(0.f, 0.f), FVector2D(640.f, 480.f), FVector2D(0.f, 0.f), 1, 1);

	// Effect
	UImageManager::GetInst().CreateCutSprite("BackGround.png", "Stars", FVector2D(640.f, 3392.f), FVector2D(8.f, 8.f), FVector2D(0.f, 0.f), 3, 3);
}

void V6ContentsCore::PlayerImageLoad()
{
	float X = 48.f;
	float Y = 42.f;
	// 비리디언(Viridian) - 선장(Captain)
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan Right", FVector2D(X * 0, Y * 0), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan Left", FVector2D(X * 1, Y * 0), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan rRight", FVector2D(X * 2, Y * 0), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan rLeft", FVector2D(X * 3, Y * 0), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan Sad Right", FVector2D(X * 0, Y * 1), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan Sad Left", FVector2D(X * 1, Y * 1), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan Sad rRight", FVector2D(X * 2, Y * 1), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Cyan Sad rLeft", FVector2D(X * 3, Y * 1), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	// 바이올렛(Violet) - 박사(Doctor)
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink Right", FVector2D(X * 0, Y * 2), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink Left", FVector2D(X * 1, Y * 2), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink rRight", FVector2D(X * 2, Y * 2), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink rLeft", FVector2D(X * 3, Y * 2), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink Sad Right", FVector2D(X * 0, Y * 3), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink Sad Left", FVector2D(X * 1, Y * 3), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink Sad rRight", FVector2D(X * 2, Y * 3), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Pink Sad rLeft", FVector2D(X * 3, Y * 3), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	// 빅토리아(Victoria) - 박사(Doctor)
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red Right", FVector2D(X * 0, Y * 4), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red Left", FVector2D(X * 1, Y * 4), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red rRight", FVector2D(X * 2, Y * 4), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red rLeft", FVector2D(X * 3, Y * 4), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red Sad Right", FVector2D(X * 0, Y * 5), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red Sad Left", FVector2D(X * 1, Y * 5), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red Sad rRight", FVector2D(X * 2, Y * 5), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Red Sad rLeft", FVector2D(X * 3, Y * 5), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	// 버디그리스(Verdigris) - 항해사(Chief)
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue Right", FVector2D(X * 0, Y * 6), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue Left", FVector2D(X * 1, Y * 6), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue rRight", FVector2D(X * 2, Y * 6), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue rLeft", FVector2D(X * 3, Y * 6), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue Sad Right", FVector2D(X * 0, Y * 7), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue Sad Left", FVector2D(X * 1, Y * 7), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue Sad rRight", FVector2D(X * 2, Y * 7), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Blue Sad rLeft", FVector2D(X * 3, Y * 7), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	// 비텔러리(Vitellary) - 교수(Professor)
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow Right", FVector2D(X * 0, Y * 8), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow Left", FVector2D(X * 1, Y * 8), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow rRight", FVector2D(X * 2, Y * 8), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow rLeft", FVector2D(X * 3, Y * 8), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow Sad Right", FVector2D(X * 0, Y * 9), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow Sad Left", FVector2D(X * 1, Y * 9), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow Sad rRight", FVector2D(X * 2, Y * 9), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Yellow Sad rLeft", FVector2D(X * 3, Y * 9), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	// 버밀리언(Vermilion) - 장교(Officer)
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green Right", FVector2D(X * 0, Y * 10), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green Left", FVector2D(X * 1, Y * 10), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green rRight", FVector2D(X * 2, Y * 10), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green rLeft", FVector2D(X * 3, Y * 10), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green Sad Right", FVector2D(X * 0, Y * 11), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green Sad Left", FVector2D(X * 1, Y * 11), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green Sad rRight", FVector2D(X * 2, Y * 11), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Green Sad rLeft", FVector2D(X * 3, Y * 11), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	// 유령 
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey Right", FVector2D(X * 0, Y * 12), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey Left", FVector2D(X * 1, Y * 12), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey rRight", FVector2D(X * 2, Y * 12), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey rLeft", FVector2D(X * 3, Y * 12), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);

	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey Sad Right", FVector2D(X * 0, Y * 13), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey Sad Left", FVector2D(X * 1, Y * 13), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey Sad rRight", FVector2D(X * 2, Y * 13), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Player.png", "Guys:: Grey Sad rLeft", FVector2D(X * 3, Y * 13), FVector2D(24.f, 42.f), FVector2D(0.f, 0.f), 2, 2);
}

void V6ContentsCore::FontImageLoad()
{
	float Y = 96.f; 
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: White", FVector2D(0.f, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Cyan", FVector2D(0.f, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Pink", FVector2D(0.f, Y * 2), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Red", FVector2D(0.f, Y * 3), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Blue", FVector2D(0.f, Y * 4), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Yellow", FVector2D(0.f, Y * 5), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Green", FVector2D(0.f, Y * 6), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "Fonts:: Grey", FVector2D(0.f, Y * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 16, 96);

	float X = 48.f;
	Y = 48.f;
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: White", FVector2D(256.f + X * 0, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Cyan", FVector2D(256.f + X * 1, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Pink", FVector2D(256.f + X * 2, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Red", FVector2D(256.f + X * 3, Y * 0), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Blue", FVector2D(256.f + X * 0, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Yellow", FVector2D(256.f + X * 1, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Green", FVector2D(256.f + X * 2, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);
	UImageManager::GetInst().CreateCutSprite("Fonts & Text.png", "TextBoxs:: Grey", FVector2D(256.f + X * 3, Y * 1), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 3, 9);

}

void V6ContentsCore::BackGroundObjectImageLoad()
{
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "SadElephant", FVector2D(8.f, 182.f), FVector2D(928.f, 640.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "PlayTimeIcon", FVector2D(318.f, 126.f), FVector2D(34.f, 34.f), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "CommsRelayRadar", FVector2D(834.f, 26.f), FVector2D(128.f, 128.f), FVector2D(6.f, 0.f), 4, 4);
}

void V6ContentsCore::InterObjectImageLoad()
{
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "Terminal", FVector2D(8.f, 26.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "WarpToken", FVector2D(8.f, 78.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "CheckPoint", FVector2D(8.f, 130.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "Trinket", FVector2D(162.f, 26.f), FVector2D(32.f, 32.f), FVector2D(0.f, 0.f), 1, 1);
}

void V6ContentsCore::EnermyImageLoad()
{
	float ColorOffsetY = 268.f;

	float StartPosX = 0.f;
	float StartPosY = 0.f;
	FVector2D CuttingSize = FVector2D(44.f, 64.f);
	int UnitXCount = 4;
	int UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::01 Stop Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::02 Stop Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::03 Stop Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::04 Stop Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::05 Stop Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::06 Stop Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::07 Stop Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 200.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(56.f, 64.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::08 Hellmet Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::09 Hellmet Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::10 Hellmet Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::11 Hellmet Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::12 Hellmet Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::13 Hellmet Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::14 Hellmet Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 70.f;
	CuttingSize = FVector2D(64.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::15 Noise Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::16 Noise Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::17 Noise Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::18 Noise Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::19 Noise Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::20 Noise Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::21 Noise Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 108.f;
	CuttingSize = FVector2D(40.f, 40.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::22 Yes Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::23 Yes Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::24 Yes Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::25 Yes Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::26 Yes Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::27 Yes Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::28 Yes Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 184.f;
	StartPosY = 108.f;
	CuttingSize = FVector2D(48.f, 50.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::29 Ghost Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::30 Ghost Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::31 Ghost Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::32 Ghost Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::33 Ghost Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::34 Ghost Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::35 Ghost Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 154.f;
	CuttingSize = FVector2D(32.f, 38.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::36 Spear Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::37 Spear Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::38 Spear Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::39 Spear Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::40 Spear Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::41 Spear Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::42 Spear Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(60.f, 28.f);
	UnitXCount = 5;
	UnitTotalCount = 5;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::43 Number Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::44 Number Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::45 Number Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::46 Number Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::47 Number Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::48 Number Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::49 Number Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 232.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::50 Ribbon Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::51 Ribbon Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::52 Ribbon Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::53 Ribbon Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::54 Ribbon Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::55 Ribbon Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::56 Ribbon Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 324.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(128.f, 92.f);
	UnitXCount = 2;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::57 Dump Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::58 Dump Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::59 Dump Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::60 Dump Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::61 Dump Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::62 Dump Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::63 Dump Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 594.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::64 Clock Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::65 Clock Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::66 Clock Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::67 Clock Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::68 Clock Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::69 Clock Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::70 Clock Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 594.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::64 Clock Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::65 Clock Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::66 Clock Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::67 Clock Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::68 Clock Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::69 Clock Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::70 Clock Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
}
