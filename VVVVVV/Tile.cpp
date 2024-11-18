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
	Sprite = CreateDefaultSubObject<USpriteRenderer>();
	Sprite->SetSprite("Debug Tile", 0);
	Sprite->SetSpriteScale(1.f, 0);

	AnimationTileSetup();
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

}
