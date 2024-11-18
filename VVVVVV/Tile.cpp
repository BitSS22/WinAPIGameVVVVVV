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

	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Debug Tile", 0);
	Sprite->SetSpriteScale(1.f, 0);
	Sprite->SetOrder(ERenderOrder::TILE);

	AnimationTileSetup();
}

void ATile::Tick()
{
	Super::Tick();

	switch (TileType)
	{
	case ETileType::None:
		break;	
	case ETileType::BackGround:
		break;
	case ETileType::Collision:
		break;
	case ETileType::Spike:
		break;
	case ETileType::Animation:
		break;
	case ETileType::Rail:
		break;
	case ETileType::Last:
		break;
	default:
		break;
	}
}

void ATile::SetTile(std::string_view _Name, int _Index, ETileType _TileType)
{
	Sprite->SetSprite(_Name, _Index);
	TileType = _TileType;

	switch (_TileType)
	{
	case ETileType::None:
	case ETileType::BackGround:
	case ETileType::Collision:
	case ETileType::Spike:
		Sprite->OffAnimation();
		return;
	case ETileType::Animation:
	case ETileType::Rail:
		Sprite->ChangeAnimation(_Name, false);
		return;
	}

	MSGASSERT(nullptr, "Unknown Tile Type");
}

void ATile::AnimationTileSetup()
{
	Sprite->CreateAnimation("AnimationTiles::01 Animation Cyan", "AnimationTiles::01 Animation Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("AnimationTiles::02 Animation Pink", "AnimationTiles::02 Animation Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("AnimationTiles::03 Animation Red", "AnimationTiles::03 Animation Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("AnimationTiles::04 Animation Blue", "AnimationTiles::04 Animation Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("AnimationTiles::05 Animation Yellow", "AnimationTiles::05 Animation Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("AnimationTiles::06 Animation Green", "AnimationTiles::06 Animation Green", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 }, EGameConst::AnimationTime, true);
	
	Sprite->CreateAnimation("RailTiles::01 Rail Left Cyan", "RailTiles::01 Rail Left Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::02 Rail Left Pink", "RailTiles::02 Rail Left Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::03 Rail Left Red", "RailTiles::03 Rail Left Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::04 Rail Left Blue", "RailTiles::04 Rail Left Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::05 Rail Left Yellow", "RailTiles::05 Rail Left Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::06 Rail Left Green", "RailTiles::06 Rail Left Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::07 Rail Left Grey", "RailTiles::07 Rail Left Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	
	Sprite->CreateAnimation("RailTiles::08 Rail Right Cyan", "RailTiles::08 Rail Right Cyan", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::09 Rail Right Pink", "RailTiles::09 Rail Right Pink", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::10 Rail Right Red", "RailTiles::10 Rail Right Red", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::11 Rail Right Blue", "RailTiles::11 Rail Right Blue", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::12 Rail Right Yellow", "RailTiles::12 Rail Right Yellow", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::13 Rail Right Green", "RailTiles::13 Rail Right Green", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
	Sprite->CreateAnimation("RailTiles::14 Rail Right Grey", "RailTiles::14 Rail Right Grey", { 0, 1, 2, 3 }, EGameConst::AnimationTime, true);
}
