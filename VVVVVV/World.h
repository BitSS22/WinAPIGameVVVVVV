#pragma once
#include "MapData.h"

class ATileMap;
// Ό³Έν :
class AWorld : public AActor
{
private:
	AWorld();
public:
	~AWorld();

	AWorld(const AWorld& _Other) = delete;
	AWorld(AWorld&& _Other) noexcept = delete;
	AWorld& operator=(const AWorld& _Other) = delete;
	AWorld& operator=(AWorld&& _Other) noexcept = delete;

private:
	FIntPoint WorldSize = EGameConst::WorldSize;
	ATileMap* Map = nullptr;
	std::vector<std::vector<UMapData>> WorldTileData = {};
	

public:

private:

};

