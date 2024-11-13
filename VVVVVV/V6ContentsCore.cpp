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

	// Pen, Brush
	UEngineWindowImage* BackBufferImage = UEngineAPICore::GetCore()->GetMainWindow().GetBackBufferImage();
	HBRUSH OldBrush = static_cast<HBRUSH>(SelectObject(BackBufferImage->GetDC(), GetStockObject(NULL_BRUSH)));
	HPEN OldPen = static_cast<HPEN>(SelectObject(BackBufferImage->GetDC(), GetStockObject(WHITE_PEN)));
	DeleteObject(OldBrush);
	DeleteObject(OldPen);

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
	SpriteLoad();
}

void V6ContentsCore::SpriteLoad()
{
	UEngineDirectory Dir = {};
	Dir.MoveParentToDirectory("Resources");
	Dir.Append("Image");
	vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (const auto& image : ImageFiles)
		UImageManager::GetInst().Load(image.GetPathToString());

	TileImageLoad();
	BackGroundImageLoad();
	FontImageLoad();
	
	PlayerImageLoad();
	BackGroundObjectImageLoad();
	FlatformImageLoad();
	InterObjectImageLoad();
	EnermyImageLoad();
}

void V6ContentsCore::TileImageLoad()
{
	float X = 192.f;
	float Y = 64.f;
	 
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "None Tile", FVector2D(80.f, 832.f + 16.f * 7), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 1, 1);


	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::01 Type00 Cyan", FVector2D(X * 0, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::02 Type00 Pink", FVector2D(X * 1, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::03 Type00 Red", FVector2D(X * 2, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::04 Type00 Blue", FVector2D(X * 3, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::05 Type00 Yellow", FVector2D(X * 4, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::06 Type00 Green", FVector2D(X * 5, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::07 Type00 Gray", FVector2D(X * 6, Y * 11), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::08 Type01 Cyan", FVector2D(X * 0, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::09 Type01 Pink", FVector2D(X * 1, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::10 Type01 Red", FVector2D(X * 2, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::11 Type01 Blue", FVector2D(X * 3, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::12 Type01 Yellow", FVector2D(X * 4, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);
	UImageManager::GetInst().CreateCutSprite("Tileset.png", "BackGroundTiles::13 Type01 Green", FVector2D(X * 5, Y * 12), FVector2D(16.f, 16.f), FVector2D(0.f, 0.f), 12, 48);

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

void V6ContentsCore::FlatformImageLoad()
{
	float X = 64.f;
	float Y = 16.f;

	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::01 Platforms Cyan", FVector2D(X * 0, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::02 Platforms Pink", FVector2D(X * 0, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::03 Platforms Red", FVector2D(X * 0, Y * 2), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::04 Platforms Blue", FVector2D(X * 0, Y * 3), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::05 Platforms Yellow", FVector2D(X * 0, Y * 4), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::06 Platforms Green", FVector2D(X * 0, Y * 5), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::07 Platforms Grey", FVector2D(X * 0, Y * 6), FVector2D(X, Y), FVector2D(0.f, 0.f), 1, 1);

	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::08 Platforms Hide Cyan", FVector2D(X * 0, Y * 0), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::09 Platforms Hide Pink", FVector2D(X * 0, Y * 1), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::10 Platforms Hide Red", FVector2D(X * 0, Y * 2), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::11 Platforms Hide Blue", FVector2D(X * 0, Y * 3), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::12 Platforms Hide Yellow", FVector2D(X * 0, Y * 4), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::13 Platforms Hide Green", FVector2D(X * 0, Y * 5), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
	UImageManager::GetInst().CreateCutSprite("Platforms.png", "Platforms::14 Platforms Hide Grey", FVector2D(X * 0, Y * 6), FVector2D(X, Y), FVector2D(0.f, 0.f), 4, 4);
}

void V6ContentsCore::InterObjectImageLoad()
{
	UImageManager::GetInst().CreateCutSprite("Objects & Menu.png", "InterObjects::01 Terminal", FVector2D(8.f, 26.f), FVector2D(32.f, 32.f), FVector2D(6.f, 0.f), 2, 2);
}

void V6ContentsCore::EnermyImageLoad()
{
	float ColorOffsetY = 268.f;

	float StartPosX = 0.f;
	float StartPosY = 0.f;
	FVector2D CuttingSize = FVector2D(44.f, 64.f);
	int UnitXCount = 4;
	int UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::001 Stop Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::002 Stop Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::003 Stop Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::004 Stop Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::005 Stop Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::006 Stop Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::007 Stop Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 200.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(56.f, 64.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::008 Hellmet Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::009 Hellmet Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::010 Hellmet Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::011 Hellmet Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::012 Hellmet Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::013 Hellmet Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::014 Hellmet Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 70.f;
	CuttingSize = FVector2D(64.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::015 Noise Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::016 Noise Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::017 Noise Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::018 Noise Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::019 Noise Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::020 Noise Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::021 Noise Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 108.f;
	CuttingSize = FVector2D(40.f, 40.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::022 Yes Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::023 Yes Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::024 Yes Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::025 Yes Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::026 Yes Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::027 Yes Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::028 Yes Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 184.f;
	StartPosY = 108.f;
	CuttingSize = FVector2D(48.f, 50.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::029 Ghost Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::030 Ghost Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::031 Ghost Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::032 Ghost Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::033 Ghost Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::034 Ghost Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::035 Ghost Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 154.f;
	CuttingSize = FVector2D(32.f, 38.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::036 Spear Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::037 Spear Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::038 Spear Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::039 Spear Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::040 Spear Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::041 Spear Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::042 Spear Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(60.f, 28.f);
	UnitXCount = 5;
	UnitTotalCount = 5;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::043 Number Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::044 Number Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::045 Number Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::046 Number Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::047 Number Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::048 Number Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::049 Number Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 0.f;
	StartPosY = 232.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::050 Ribbon Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::051 Ribbon Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::052 Ribbon Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::053 Ribbon Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::054 Ribbon Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::055 Ribbon Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::056 Ribbon Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 324.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(128.f, 92.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::057 Dump Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::058 Dump Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::059 Dump Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::060 Dump Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::061 Dump Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::062 Dump Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::063 Dump Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 324.f;
	StartPosY = 98.f;
	CuttingSize = FVector2D(128.f, 92.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::064 Dump Reverse Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::065 Dump Reverse Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::066 Dump Reverse Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::067 Dump Reverse Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::068 Dump Reverse Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::069 Dump Reverse Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::070 Dump Reverse Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 594.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::071 Clock Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::072 Clock Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::073 Clock Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::074 Clock Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::075 Clock Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::076 Clock Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::077 Clock Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 873.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(58.f, 64.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::078 Speaker Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::079 Speaker Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::080 Speaker Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::081 Speaker Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::082 Speaker Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::083 Speaker Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::084 Speaker Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 594.f;
	StartPosY = 70.f;
	CuttingSize = FVector2D(128.f, 100.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::085 Factory Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::086 Factory Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::087 Factory Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::088 Factory Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::089 Factory Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::090 Factory Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::091 Factory Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 862.f;
	StartPosY = 70.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::092 TV Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::093 TV Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::094 TV Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::095 TV Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::096 TV Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::097 TV Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::098 TV Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 932.f;
	StartPosY = 70.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::099 TV Reverse Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::100 TV Reverse Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::101 TV Reverse Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::102 TV Reverse Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::103 TV Reverse Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::104 TV Reverse Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::105 TV Reverse Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 862.f;
	StartPosY = 160.f;
	CuttingSize = FVector2D(88.f, 20.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::106 TRUTH Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::107 TRUTH Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::108 TRUTH Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::109 TRUTH Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::110 TRUTH Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::111 TRUTH Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::112 TRUTH Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 956.f;
	StartPosY = 140.f;
	CuttingSize = FVector2D(54.f, 24.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::113 LIES Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::114 LIES Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::115 LIES Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::116 LIES Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::117 LIES Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::118 LIES Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::119 LIES Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 862.f;
	StartPosY = 170.f;
	CuttingSize = FVector2D(30.f, 48.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::120 Skull Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::121 Skull Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::122 Skull Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::123 Skull Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::124 Skull Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::125 Skull Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::126 Skull Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 330.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(36.f, 50.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::127 Mannequin Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::128 Mannequin Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::129 Mannequin Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::130 Mannequin Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::131 Mannequin Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::132 Mannequin Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::133 Mannequin Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 414.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::134 Fish Right Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::135 Fish Right Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::136 Fish Right Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::137 Fish Right Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::138 Fish Right Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::139 Fish Right Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::140 Fish Right Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 414.f;
	StartPosY = 236.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::141 Fish Left Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::142 Fish Left Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::143 Fish Left Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::144 Fish Left Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::145 Fish Left Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::146 Fish Left Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::147 Fish Left Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 566.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(120.f, 32.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::148 0008 Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::149 0008 Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::150 0008 Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::151 0008 Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::152 0008 Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::153 0008 Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::154 0008 Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 566.f;
	StartPosY = 236.f;
	CuttingSize = FVector2D(120.f, 32.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::155 8000 Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::156 8000 Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::157 8000 Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::158 8000 Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::159 8000 Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::160 8000 Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::161 8000 Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 692.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::162 Big Circle Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::163 Big Circle Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::164 Big Circle Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::165 Big Circle Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::166 Big Circle Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::167 Big Circle Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::168 Big Circle Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 762.f;
	StartPosY = 198.f;
	CuttingSize = FVector2D(64.f, 64.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::169 Big Rectangle Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::170 Big Rectangle Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::171 Big Rectangle Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::172 Big Rectangle Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::173 Big Rectangle Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::174 Big Rectangle Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::175 Big Rectangle Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1002.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(64.f, 42.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::176 Cloud Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::177 Cloud Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::178 Cloud Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::179 Cloud Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::180 Cloud Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::181 Cloud Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::182 Cloud Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1002.f;
	StartPosY = 48.f;
	CuttingSize = FVector2D(48.f, 32.f);
	UnitXCount = 1;
	UnitTotalCount = 1;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::183 Chimney Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::184 Chimney Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::185 Chimney Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::186 Chimney Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::187 Chimney Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::188 Chimney Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::189 Chimney Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1072.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::190 CD Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::191 CD Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::192 CD Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::193 CD Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::194 CD Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::195 CD Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::196 CD Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1072.f;
	StartPosY = 38.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::197 Shuriken Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::198 Shuriken Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::199 Shuriken Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::200 Shuriken Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::201 Shuriken Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::202 Shuriken Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::203 Shuriken Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1072.f;
	StartPosY = 76.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::204 Coin Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::205 Coin Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::206 Coin Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::207 Coin Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::208 Coin Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::209 Coin Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::210 Coin Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1072.f;
	StartPosY = 114.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::211 Ring Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::212 Ring Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::213 Ring Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::214 Ring Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::215 Ring Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::216 Ring Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::217 Ring Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1072.f;
	StartPosY = 152.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::218 Rectangle Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::219 Rectangle Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::220 Rectangle Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::221 Rectangle Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::222 Rectangle Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::223 Rectangle Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::224 Rectangle Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1224.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::225 Heart Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::226 Heart Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::227 Heart Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::228 Heart Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::229 Heart Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::230 Heart Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::231 Heart Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1300.f;
	StartPosY = 0.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 2;
	UnitTotalCount = 2;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::232 Broken Heart Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::233 Broken Heart Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::234 Broken Heart Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::235 Broken Heart Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::236 Broken Heart Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::237 Broken Heart Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::238 Broken Heart Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1224.f;
	StartPosY = 38.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::239 ERROR Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::240 ERROR Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::241 ERROR Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::242 ERROR Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::243 ERROR Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::244 ERROR Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::245 ERROR Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1224.f;
	StartPosY = 76.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::246 Ice Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::247 Ice Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::248 Ice Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::249 Ice Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::250 Ice Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::251 Ice Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::252 Ice Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);

	StartPosX = 1224.f;
	StartPosY = 114.f;
	CuttingSize = FVector2D(32.f, 32.f);
	UnitXCount = 4;
	UnitTotalCount = 4;
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::253 Spike Cyan", FVector2D(StartPosX, StartPosY + ColorOffsetY * 0), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::254 Spike Pink", FVector2D(StartPosX, StartPosY + ColorOffsetY * 1), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::255 Spike Red", FVector2D(StartPosX, StartPosY + ColorOffsetY * 2), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::256 Spike Blue", FVector2D(StartPosX, StartPosY + ColorOffsetY * 3), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::257 Spike Yellow", FVector2D(StartPosX, StartPosY + ColorOffsetY * 4), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::258 Spike Green", FVector2D(StartPosX, StartPosY + ColorOffsetY * 5), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
	UImageManager::GetInst().CreateCutSprite("Enemies.png", "Enemies::259 Spike Grey", FVector2D(StartPosX, StartPosY + ColorOffsetY * 6), CuttingSize, FVector2D(6.f, 6.f), UnitXCount, UnitTotalCount);
}
