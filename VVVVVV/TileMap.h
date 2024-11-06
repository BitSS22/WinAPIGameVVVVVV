#pragma once

class UTileMap : public AActor
{
public:
	UTileMap();
	UTileMap(FIntPoint _TileCount, FIntPoint _TileSize);
	~UTileMap();

	UTileMap(const UTileMap& _Other) = delete;
	UTileMap(UTileMap&& _Other) noexcept = delete;
	UTileMap& operator=(const UTileMap& _Other) = delete;
	UTileMap& operator=(UTileMap&& _Other) noexcept = delete;

public:
	FIntPoint TileCount = EEngineConst::TileCount;
	FIntPoint TileSize = EEngineConst::TileSize;
	std::vector<std::vector<AActor*>> Tiles = {};
	std::vector<std::vector<USpriteRenderer*>> BackGroundTiles = {};

public:
	virtual void BeginPlay() override;

private:

public:

};

