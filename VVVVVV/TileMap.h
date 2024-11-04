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
	FIntPoint TileCount = { 40, 30 };
	FIntPoint TileSize = { 16, 16 };
	std::vector<std::vector<AActor*>> CollisionTiles = {};
	std::vector<std::vector<USpriteRenderer*>> BackGroundTiles = {};

public:
	virtual void BeginPlay() override;

private:

public:

};

