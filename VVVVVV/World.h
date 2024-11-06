#pragma once

class ATileMap;
// Ό³Έν :
class AWorld : public AActor
{
public:
	INNER_CLASS struct RoomData;
public:
	AWorld();
	~AWorld();

	AWorld(const AWorld& _Other) = delete;
	AWorld(AWorld&& _Other) noexcept = delete;
	AWorld& operator=(const AWorld& _Other) = delete;
	AWorld& operator=(AWorld&& _Other) noexcept = delete;

private:
	FIntPoint WorldSize = EGameConst::WorldSize;
	ATileMap* TileMap = nullptr;
	std::vector<std::vector<RoomData>> Rooms = {};
	std::vector<std::vector<RoomData>> RoomsBackGround = {};


public:

private:

public:
	INNER_CLASS struct RoomData
	{
		std::string Name = {};
		int CurSpriteIndex = -1;
	};

};

