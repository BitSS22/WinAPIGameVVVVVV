#pragma once
#include <EnginePlatform/EngineWindowImage.h>

class ABackGround;

class ARoom : public AActor
{
public:
	friend class ATileMapEditorMode;
public:
	ARoom();
	ARoom(FIntPoint _TileCount, FIntPoint _TileScale);
	~ARoom();

	ARoom(const ARoom& _Other) = delete;
	ARoom(ARoom&& _Other) noexcept = delete;
	ARoom& operator=(const ARoom& _Other) = delete;
	ARoom& operator=(ARoom&& _Other) noexcept = delete;

private:
	FIntPoint TileCount = EGameConst::TileCount;
	FIntPoint TileScale = EGameConst::TileScale;
	std::vector<std::vector<USpriteRenderer*>> Tiles = {};
	std::vector<std::vector<USpriteRenderer*>> BackGroundTiles = {};
	ABackGround* BackGround = nullptr;

public:
	virtual void BeginPlay() override;

private:

public:
	FIntPoint GetOnTileIndex(FIntPoint _Pos)
	{
		FIntPoint Result = FIntPoint(_Pos.X / TileScale.X, _Pos.Y / TileScale.Y);
		if (Result.X < 0)
			Result.X = 0;
		else if (Result.X >= TileCount.X)
			Result.X = TileCount.X - 1;
		if (Result.Y < 0)
			Result.Y = 0;
		else if (Result.Y >= TileCount.Y)
			Result.Y = TileCount.Y - 1;
		return Result;
	}

};

