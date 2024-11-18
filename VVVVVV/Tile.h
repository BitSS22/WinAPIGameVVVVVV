#pragma once
#include <EngineCore/SpriteRenderer.h>

// ���� :
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
	ETileType TileType = ETileType::Last;
	USpriteRenderer* SpriteRenderer = nullptr;

public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	
	void SetTile(std::string_view _Name);

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
