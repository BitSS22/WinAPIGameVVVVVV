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
	virtual void BeginPlay() override;
	virtual void Tick() override;
	
	virtual void SetTile(std::string_view _Name, FIntPoint _Location, ETileType _TileType);

private:

public:
	void SetTileType(ETileType _Type)
	{
		TileType = _Type;
	}
	ETileType GetTileType()
	{
		return TileType;
	}

};

