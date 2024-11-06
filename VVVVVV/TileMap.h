#pragma once

class ATileMap : public AActor
{
public:
	ATileMap();
	ATileMap(FIntPoint _TileCount, FIntPoint _TileScale);
	~ATileMap();

	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

public:
	FIntPoint TileCount = EGameConst::TileCount;
	FIntPoint TileScale = EGameConst::TileScale;
	std::vector<std::vector<AActor*>> Tiles = {};
	std::vector<std::vector<USpriteRenderer*>> BackGroundTiles = {};

public:
	virtual void BeginPlay() override;

private:

public:

};

