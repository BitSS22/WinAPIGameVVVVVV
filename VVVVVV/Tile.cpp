#include "pch.h"
#include "Tile.h"

ATile::ATile()
{
}

ATile::~ATile()
{
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	SpriteRenderer->CreateAnimation("AnimationTiles::01 Animation Cyan", "AnimationTiles::01 Animation Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("AnimationTiles::02 Animation Pink", "AnimationTiles::02 Animation Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("AnimationTiles::03 Animation Red", "AnimationTiles::03 Animation Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("AnimationTiles::04 Animation Blue", "AnimationTiles::04 Animation Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("AnimationTiles::05 Animation Yellow", "AnimationTiles::05 Animation Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("AnimationTiles::06 Animation Green", "AnimationTiles::06 Animation Green", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, EGameConst::AnimationTime, true);
	
	SpriteRenderer->CreateAnimation("RailTiles::01 Rail Left Cyan", "RailTiles::01 Rail Left Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::02 Rail Left Pink", "RailTiles::02 Rail Left Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::03 Rail Left Red", "RailTiles::03 Rail Left Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::04 Rail Left Blue", "RailTiles::04 Rail Left Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::05 Rail Left Yellow", "RailTiles::05 Rail Left Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::06 Rail Left Green", "RailTiles::06 Rail Left Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::07 Rail Left Grey", "RailTiles::07 Rail Left Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	
	SpriteRenderer->CreateAnimation("RailTiles::08 Rail Right Cyan", "RailTiles::08 Rail Right Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::09 Rail Right Pink", "RailTiles::09 Rail Right Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::10 Rail Right Red", "RailTiles::10 Rail Right Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::11 Rail Right Blue", "RailTiles::11 Rail Right Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::12 Rail Right Yellow", "RailTiles::12 Rail Right Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::13 Rail Right Green", "RailTiles::13 Rail Right Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	SpriteRenderer->CreateAnimation("RailTiles::14 Rail Right Grey", "RailTiles::14 Rail Right Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);

	SpriteRenderer->SetComponentScale(FVector2D(TileScale.X, TileScale.Y));
	SpriteRenderer->SetComponentLocation(FVector2D(TileScale.X * x + TileScale.X / 2, TileScale.Y * y + TileScale.Y / 2));
	SpriteRenderer->SetSprite("Debug Tile", 0);
	SpriteRenderer->SetOrder(ERenderOrder::TILE);
}

void ATile::Tick()
{
	Super::Tick();

}

void ATile::SetTile(std::string_view _Name)
{
	SpriteRenderer->SetSprite(_Name, 0);
	string UpperName = UEngineString::ToUpper(_Name);

	if (UpperName.find() != std::string::npos)
}

