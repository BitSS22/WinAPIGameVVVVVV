#pragma once
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class ATile : public AActor
{
public:
	ATile();
	~ATile();

	ATile(const ATile& _Other) = delete;
	ATile(ATile&& _Other) noexcept = delete;
	ATile& operator=(const ATile& _Other) = delete;
	ATile& operator=(ATile&& _Other) noexcept = delete;

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	ETileType TileType = ETileType::Last;

public:	
	virtual void SetTile(std::string_view _Name) = 0;

private:

public:
	ETileType GetTileType()
	{
		return TileType;
	}

};

